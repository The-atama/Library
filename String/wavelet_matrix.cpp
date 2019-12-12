#include <bits/stdc++.h>
using namespace std;

struct FullyIndexableDictionary{
  static const int smallBlockSize = 16;
  static const int bigBlockSize = 1024;
  static constexpr int smallInBig = bigBlockSize / smallBlockSize;
  
  vector<uint16_t> bit; // raw data

  vector<uint32_t> bigBlockAcc; // not succinct, optimal : 22 bit
  vector<vector<uint16_t>> smallBlockAcc; // not succinct, optimal : 10 bit

  int length;
  int bigBlockNum;
  int smallBlockNum;

  bool is_built;

  FullyIndexableDictionary(){}

  FullyIndexableDictionary(int len) : length(len),is_built(false) {
    bigBlockNum = (length+bigBlockSize-1)/bigBlockSize;
    smallBlockNum = bigBlockNum * smallInBig;
    bit.assign(smallBlockNum,0);
    bigBlockAcc.assign(bigBlockNum+1,0);
    smallBlockAcc.assign(bigBlockNum,vector<uint16_t>(smallInBig,0));
  }

  void set(int id){
    int sid = id / smallBlockSize;
    int offset = id % smallBlockSize;
    bit[sid] |= (uint16_t)(1u<<offset);
  }

  void unset(int id){
    int sid = id / smallBlockSize;
    int offset = id % smallBlockSize;
    bit[sid] &= (uint16_t)(~(1u<<offset));
  }

  bool operator[] (int id){
    int sid = id / smallBlockSize;
    int offset = id % smallBlockSize;
    return (bool)((bit[sid]>>offset)&1u);
  }

  void build(){
    is_built = true;
    bigBlockAcc[0] = 0;
    for(int i=0;i+1<bigBlockAcc.size();i++){
      smallBlockAcc[i][0] = 0;
      for(int j=0;j+1<smallBlockAcc[i].size();j++){
        smallBlockAcc[i][j+1] = smallBlockAcc[i][j] + __builtin_popcount(bit[i*smallInBig+j]);
      }
      bigBlockAcc[i+1] = bigBlockAcc[i] + smallBlockAcc[i].back() + __builtin_popcount(bit[(i+1)*smallInBig-1]);
    }
  }

  int rank(int id) const {
    assert(is_built);
    int bid = id / bigBlockSize;
    int sid = (id % bigBlockSize) / smallBlockSize;
    int offset = id % smallBlockSize;
    uint16_t rem = bit[bid * smallInBig + sid] & ((1u << offset) - 1u);
    return bigBlockAcc[bid] + smallBlockAcc[bid][sid] + __builtin_popcount(rem);
  }
  
  // number of b in [0,id)
  int rank(int b,int id) const {
    if (b==1) return rank(id);
    else return id-rank(id);
  }
  
  // return the position of num-th b
  // namely, the minimum id that holds rank(b,id+1) = num+1
  // attention : num is 0-indexed
  int select(int b,int num) const {
    assert(is_built);
    if (num < 0 || num >= rank(b,length)) return -1;
    int l = 0, r = length;
    while(r-l>1){
      int mid = (l+r)/2;
      if(rank(b,mid)>=num+1) r = mid;
      else l = mid;
    }
    return l;
  }
  int select(int num){
    return select(1,num);
  }
  int select(int b,int num,int l){
    return select(b,num+rank(b,l));
  }
};


// T must be unsigned type

template<class T,int LOG>
struct WaveletMatrix{
  int length;
  FullyIndexableDictionary mat[LOG];
  int zeroNum[LOG];
  int buf1[LOG],buf2[LOG];

  WaveletMatrix(vector<T> data){
    length = data.size();
    vector<T> lv(length),rv(length);
    for(int i=0;i<LOG;i++){
      mat[i] = FullyIndexableDictionary(length+1);
      int lp = 0,rp = 0;
      for(int j=0;j<length;j++){
        int bit = (data[j]>>(LOG-i-1))&(T(1));
        if(bit==1){
          rv[rp++] = data[j];
          mat[i].set(j);
        }else{
          lv[lp++] = data[j];
        }
      }
      mat[i].build();
      zeroNum[i] = lp;
      //cout << lp << ' ' << rp << endl;
      for(int j=0;j<rp;j++)lv[lp+j]=rv[j];
      swap(data,lv);
      /*cout << zeroNum[i] << endl;
      for(int j=0;j<length;j++){
        cout << data[j] << ' ';
      }
      cout << endl; */
    }
  }

  // get id-th element
  T access(int id){
    T res = T(0);
    for(int i=0;i<LOG;i++){
      int bit = mat[i][id];
      res = (res<<1)|bit;
      id = mat[i].rank(bit,id)+zeroNum[i]*bit;
    }
    return res;
  }

  // number of v in [0,id)
  int rank(T v,int id){
    int l = 0,r = id;
    for(int i=0;i<LOG;i++){
      buf1[i] = l;
      buf2[i] = r;
      int bit = (v>>(LOG-i-1))&(T(1));
      l = mat[i].rank(bit,l)+zeroNum[i]*bit;
      r = mat[i].rank(bit,r)+zeroNum[i]*bit;
    }
    return r-l;
  }

  // position of num-th v
  // id is 0-indexed
  int select(T v,int num){
    rank(v,length); // store path in buf
    for(int i=LOG-1;i>=0;i--){
      int bit = (v>>(LOG-i-1))&(T(1));
      num = mat[i].select(bit,num,buf1[i]);
      if(num>=buf2[i]||num<0)return -1;
      num -= buf1[i];
    }
    return num;
  }

  int select(T v,int k,int l){
    return select(v,k+rank(v,l));
  }

  // k-th largest value
  T quantile(int l,int r,int k){
    if ( r-l<=k || k<0 ) return -1;
    T res = T(0);
    for(int i=0;i<LOG;i++){
      int lp = mat[i].rank(1,l);
      int rp = mat[i].rank(1,r);
      if(rp-lp>k){
        l = lp + zeroNum[i];
        r = rp + zeroNum[i];
        res |= (T(1)<<(LOG-i-1));
      }else{
        k -= (rp-lp);
        l -= lp;
        r -= rp;
      }
    }
    assert(k==0);
    return res;
  }

  T kth_max(int l,int r,int k){
    return quantile(l,r,k);
  }
  
  T kth_min(int l,int r,int k){
    return quantile(l,r,r-l-1-k);
  }

  // auxiliary function for range_freq
  int freq_dfs(int depth,int l,int r,T val,T low,T high){
    if(l==r)return 0;
    if(depth==LOG)return (low<=val&&val<high)?r-l:0;
    T right_val = ((T(1)<<(LOG-depth-1))|val);
    T right_most = (((T(1)<<(LOG-depth-1))-1)|right_val);
    if(right_most<low||high<=val)return 0;
    if(low<=val&&right_most<high)return r-l;
    int lp = mat[depth].rank(1,l);
    int rp = mat[depth].rank(1,r);
    int lch = freq_dfs(depth+1,l-lp,r-rp,val,low,high);
    int rch = freq_dfs(depth+1,lp+zeroNum[depth],rp+zeroNum[depth],right_val,low,high);
    return lch+rch;
  }

  // occurence of value of [low,high) in [l,r)
  int rangefreq(int l,int r,T low,T high){
    return freq_dfs(0,l,r,T(0),low,high);
  }

  pair<int,int> less_equal(int l,int r,T v){
    int lessNum = 0;
    for(int i=0;i<LOG;i++){
      buf1[i] = l;
      buf2[i] = r;
      int bit = (v>>(LOG-i-1))&(T(1));
      if(bit)lessNum += (r-mat[i].rank(bit,r))-(l-mat[i].rank(bit,l));
      l = mat[i].rank(bit,l)+zeroNum[i]*bit;
      r = mat[i].rank(bit,r)+zeroNum[i]*bit;
    }
    return make_pair(lessNum,r-l);
  }

  int less_freq(int l,int r,T v){
    return less_equal(l,r,v).first;
  }

  int less_equal_freq(int l,int r,T v){
    pair<int,int> res = less_equal(l,r,v);
    return res.first + res.second;
  }

  int next_value(int l,int r,T v){
    int k = less_equal_freq(l,r,v);
    if(k==r-l)return -1;
    else return kth_min(l,r,k);
  }

  int prev_value(int l,int r,T v){
    int k = less_freq(l,r,v);
    if(k==0)return -1;
    else return kth_min(l,r,k-1);
  }
};

struct SuffixArray{
  string s;
  vector<int> sa;
  vector<int> rank;
  vector<int> lcp;
  explicit SuffixArray(string s):s(s){
    int n = s.size();
    sa.resize(n+1);
    rank.resize(n+1);
    vector<int> tmp(n+1);
    for(int i=0;i<=n;i++){
      rank[i] = (i<n)?s[i]:-1;
      sa[i] = i;
    }
    for(int k=1;k<=n;k*=2){
      auto compare_sa = 
        [&](const int &i,const int &j){
           if(rank[i]!=rank[j])return rank[i]<rank[j];
           else{
             int ri=(i+k<=s.size())?rank[i+k]:-1;
             int rj=(j+k<=s.size())?rank[j+k]:-1;
             return ri<rj;
           }
        };
      sort(sa.begin(),sa.end(),compare_sa);
      tmp[sa[0]]=0;
      for(int i=1;i<=n;i++)tmp[sa[i]]=tmp[sa[i-1]]+(compare_sa(sa[i-1],sa[i])?1:0);
      for(int i=0;i<=n;i++)rank[i]=tmp[i];
    }
  }
  size_t size() const {
    return s.size();
  }
  int operator [] (int id) const {
    return sa[id];
  }
  bool contain(string t){
    int l = 0,r = s.size()+1;
    while(r-l>1){
      int mid = (l+r)/2;
      if(s.compare(sa[mid],t.size(),t)<0){
        l = mid;
      }else{
        r = mid;
      }
    }
    return s.compare(sa[r],t.size(),t)==0;
  }
};
struct LongestCommonPrefix{
  const SuffixArray &sa;
  vector<int> lcp,rank;
  explicit LongestCommonPrefix(const SuffixArray &sa):sa(sa){
    int n = sa.size();
    lcp.resize(sa.size()+1);
    rank.resize(sa.size()+1);
    for(int i=0;i<=sa.size();i++){
      rank[sa[i]]=i;
    }
    int h = 0;
    lcp[0] = 0;
    for(int i=0;i<sa.size();i++){
      int j = sa[rank[i]-1];
      if(h>0)h--;
      for(;i+h<n&&j+h<n;h++)if(sa.s[i+h]!=sa.s[j+h])break;
      lcp[rank[i]-1] = h;
    }
  }
  int operator [] (int id) const {
    assert(id>=0&&id<lcp.size());
    return lcp[id];
  }
};

struct BurrowsWheelerTransform{
  vector<char> bwt;
  const SuffixArray &sa;
  explicit BurrowsWheelerTransform(const SuffixArray &sa):sa(sa){
    bwt.resize(sa.size()+1);
    for(int i=0;i<bwt.size();i++){
      if(sa[i]==0)bwt[i] = (char)7; // dummy
      else bwt[i] = sa.s[sa[i]-1];
    }
  }
  char operator [] (int id) const {
    return bwt[id];
  }
  size_t size(){
    return bwt.size();
  }
};

pair<int,int> searchFMIndex(
    SuffixArray &sa,
    WaveletMatrix<unsigned char,8> &wm,
    vector<int> &lessCount,
    string t){
  int l = 0, r = sa.size()+1; // because of dummy character
  for(int i=0;i<t.size();i++){
    unsigned char c = t[t.size()-1-i];
    //cout << wm.rank(c,l) << ' ' << wm.rank(c,r) << endl;
    l = lessCount[c]+wm.rank(c,l);
    r = lessCount[c]+wm.rank(c,r);
    //cout << "wavelet " << l << ' ' << r << endl;
    if(l>=r)return make_pair(-1,-1);
  }
  return make_pair(l,r-1);
}

pair<int,int> contain(string s,string t){
  SuffixArray sa(s);
  BurrowsWheelerTransform bwt(sa);
  vector<unsigned char> bw;
  for(int i=0;i<bwt.size();i++){
    bw.push_back((unsigned char)bwt[i]);
  }
  WaveletMatrix<unsigned char,8> wm(bw);

  s += ((char)7); // dummy
  vector<int> lessCount(256);
  for(int i=0;i<s.size();i++){
    lessCount[s[i]+1]++;
  }
  for(int i=1;i<lessCount.size();i++){
    lessCount[i] += lessCount[i-1];
  }
  return searchFMIndex(sa,wm,lessCount,t);
}

int main(){
  FullyIndexableDictionary FID(10000);
  FID.set(12);
  FID.set(21);
  FID.set(33);
  FID.build();
  cout << FID.select(1,2) << endl;
  string s = "abracadabra";
  vector<unsigned char> v;
  for(int i=0;i<s.size();i++)v.push_back((unsigned char)s[i]);
  WaveletMatrix<unsigned char,8> wm(v);
  cout << wm.rangefreq(2,8,'b','r') << endl;
  cout << contain("abra","br").first << endl;
  return 0;
}

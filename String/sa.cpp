#include <bits/stdc++.h>
using namespace std;
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
};

int main(){
  string s;
	cin >> s;
	SuffixArray sa(s);
  LongestCommonPrefix lcp(sa);
	for(int i=0;i<=s.size();i++){
		cout << setw(3) << sa[i] << ' ' << s.substr(sa[i]) << endl;
	}
	return 0;
}

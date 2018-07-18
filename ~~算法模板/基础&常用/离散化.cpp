int n;
int a[MAX];

vector<int>v;
int getid(int x){return lower_bound(v.begin(),v.end(),x)-v.begin()+1;}

int main()
{
    for(int i=1;i<=n;i++)v.pb(a[i]);
    sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
}


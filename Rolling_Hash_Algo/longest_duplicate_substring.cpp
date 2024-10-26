class Solution {
#define p 1000007
#define alphaLen 26
#define globalFirstChar 'a'

vector<int> rollingList;

private: 
bool match(string input, int inputSize, int windowSize, string& pattern)
{
	unordered_map<int,vector<int>> map;

	// Slide till first window
	int hash = 0;
	for(int i = 0; i < windowSize ; i++)
	{
		hash = (hash*alphaLen + (input[i] - globalFirstChar + 1))%p;
        cout << input[i] << " " << hash << " "; 
	}
    cout << windowSize <<" hash value " << hash << endl;
	map[hash].push_back(0);
	// Sliding Window for pattern matching
	for(int j = windowSize ; j < inputSize; j++)
	{
        // removal of first char of currentWindow
        //((1392 - 26^2)*('b' - 'a' + 1)%1000007 = 40
        // + p is used to handle -ve values
		hash = ((hash - rollingList[windowSize-1] * (input[j - windowSize] - globalFirstChar + 1))%p + p)%p; 
        cout << "hash value : "<< hash << endl; 
        //((40*26)('a' - 'a' + 1) *mod* 1000007 = 1041
		hash = (hash*alphaLen + (input[j] - globalFirstChar + 1))%p;
        cout << "hash value : "<< hash << endl; 
		if(map.find(hash) != map.end())
		{
            // matching each characters for further validations
			for(auto startIdx : map[hash])
			{
				string temp = input.substr(startIdx,windowSize);
				string curr = input.substr(j - windowSize + 1,windowSize);
				if(temp.compare(curr) == 0)
				{
					pattern = temp;
					return true;
				}
			}
		}
        //appending vector value for hash key
        map[hash].push_back(j - windowSize + 1);
	}
	return false;
}

public:
    string longestDupSubstring(string str) {
    int n = str.size();
    rollingList.resize(n);
    rollingList[0] = 1;
    for(int i = 1; i < n; i++)
    {
        rollingList[i] = (alphaLen*rollingList[i-1])%p;
    }
    string result = "" , temp;
    int low = 1;
    int high = n - 1;
    while(low <= high)
    {
        temp = "";
        int mid = low + (high - low)/2;
        bool flag = match(str,n,mid,temp);
        if(flag)
        {
            if(temp.size() > result.size())
            {
                result = temp;
            }
            low = mid + 1;

        }
        else
        {
            high = mid - 1;
        }
    }
    return result;
    }
};
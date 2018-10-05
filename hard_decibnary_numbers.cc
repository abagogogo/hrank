// Discussion: https://www.hackerrank.com/challenges/decibinary-numbers/forum?h_l=interview&page=16&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming

/*
Idea: for each decimal number, find its number of decibinary forms, until we reach decimal N and 1e16 decibinaries.
N can be represented as decibinary form at most M bits.
Denote g[n][m] = number of all decibinaries which is n in decimal and has at most m bits,
gs[n]: number of all decibinaries which is n in decimal.
For example:
g[0][m] = 1, m = 1 - M
g[1][m] = 1, m = 1 - M
g[2][1] = 1, g[2][2] = ... = g[2][M] = 2
...
For decimal 4:
g[4][1] = 1, g[4][2] = g[4][1] + g[2][1] + g[0][1]
g[4][1] is when the higher bit is 0
g[2][1] is when the higher bit is 1
g[0][1] is when the higher bit is 2
Similarly, for decimal 8:
g[8][1] = 1, g[8][2] = g[8][1] + g[6][1] + g[4][1] + g[2][1] + g[0][1] (decrement by 2)
g[8][3] = g[8][2] + g[4][2] + g[0][2] (note decrement by 4 because highest bit is 4)
Optimization:
- find the minimum N and M
- use binary searches (std::lower_bound)
*/

typedef long long ll;

ll N =  285133;
size_t M = 19;

ll tm = 0;

vector<vector<ll> > g(N+1, vector<ll>(M+1, 0));
vector<ll> gs;

void decibinaryNumbers_helper(string &db, ll d, ll n, size_t m) {
    // get n-th decibinary of decimal d
    if (n == 1 && g[d][1]) {
        db += string(m-1, '0') + std::to_string(d);
        return;
    }
    auto it = std::lower_bound(g[d].begin(), g[d].end(), n);
    int j = it - g[d].begin();
    ll y0 = g[d][j-1];
    ll y = y0;
    ll a = pow(2, j-1);
    ll k = d - a;
    int c = 9;
    string s;
    while (k >= 0 && c--) {
        y0 = y;
        y += g[k][j-1];
        if (y >= n) {
            s = std::to_string(9-c);
            decibinaryNumbers_helper(s, k, n-y0, j-1);
            if (db.size() && s.size() < m)
                s = string(m-s.size(), '0') + s;
            db += s;
            return;
        }
        k -= a;
    }
}

ll decibinaryNumbers(ll x) {
    if (x == 1)
        return 0;
    string db;
    auto it = std::lower_bound(gs.begin(), gs.end(), x);
    ll d = it-gs.begin();
    it--;
    decibinaryNumbers_helper(db, d, x-(*it), M);
    ll z;
    stringstream ss(db);
    ss >> z;
    return z;
}

void dp() {
    // the following procedure can be used to find minimum N and M
    // first use big N and M
    // once while exits, i is the minimum N, log2(i)+1 is the minimum M
    ll i = 0, x = 0;
    while (x < 1e16) {
        g[i][1] = (i>=0 && i<=9);
        for (size_t j=2; j<=M; j++) {
            ll a = pow(2, j-1);
            ll k = i;
            int c = 10;
            while (k >= 0 && c--) {
                g[i][j] += g[k][j-1];
                k -= a;
            }
        }
        x += g[i][M];
        gs.push_back(x);
        i++;
    }
}

int main () {
    dp();
    cout << decibinaryNumbers(1e10) << endl;
		return 0;
}
-1|Add CommentPermalink


inginer_a_dinu 2 years ago
Hi,

I post my code here:

static long dbtodeci(long db)
        {
            int p = 0; long sum = 0;
            while (db != 0)
            {
                sum += (db % 10) * Convert.ToInt64(Math.Pow(2, p));
                db /= 10; p++;
            }
            return sum;
        }
        

        static void Main(string[] args)
        {
            long x; int index;
            List<long> numsdec = new List<long>();
            List<long> numsdb = new List<long>();
            // here you decide how many values to be precomputed
            for (long i = 0; i < 1000; i++)
            {
                x = dbtodeci(i);
                if (numsdec.Exists(k => k == x))
                {
                    index = numsdec.FindLastIndex(k => k == x);
                    numsdec.Insert(index + 1, x);
                    numsdb.Insert(index + 1, i);
                }
                else
                {
                    numsdec.Add(x);
                    numsdb.Add(x);
                }
            }

            List<int> indexes = new List<int>();
            Console.Write("nb of queries: ");
            int q = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < q; i++)
            {
                int xth = Convert.ToInt32(Console.ReadLine());
                indexes.Add(xth - 1);
            }
            foreach (int i in indexes)
                Console.WriteLine(numsdb[i]);
        }

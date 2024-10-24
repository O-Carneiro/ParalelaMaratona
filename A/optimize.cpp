#include<bits/stdc++.h>
#include<pthread.h>
#include<atomic> 
using namespace std;

#define maratona std::ios_base::sync_with_stdio(false);
#define muito std::cout.tie(NULL);
#define coxa std::cin.tie(NULL);
#define MAX 5012
#define NUM_CORES 4 
#define MAX_THREADS (4 * NUM_CORES) 

pthread_mutex_t memo_mutex;  
std::atomic<int> active_threads(0); 

int n, k;
int file_size[MAX];
int memo[MAX][60][60][60];

struct dp_args {
    int i;
    int capacity1;
    int capacity2;
    int capacity3;
};

//precisa declarar antes pra usar na thread
int dp(int i, int capacity1, int capacity2, int capacity3);

void* dp_thread(void* args) {
    dp_args* data = (dp_args*) args;

    int result = dp(data->i, data->capacity1, data->capacity2, data->capacity3);

    active_threads--;

    return (void*)(intptr_t) result;
}

int dp(int i, int capacity1, int capacity2, int capacity3) {
    int r1, r2, r3, r4;
    r1 = r2 = r3 = r4 = 0;

    if (i == n) return 0;

    pthread_mutex_lock(&memo_mutex);
    if (memo[i][capacity1][capacity2][capacity3] != -1) {
        int memo_result = memo[i][capacity1][capacity2][capacity3];
        pthread_mutex_unlock(&memo_mutex); 
        return memo_result;
    }
    pthread_mutex_unlock(&memo_mutex);

    pthread_t t2, t3, t4;
    bool create_t2 = false, create_t3 = false, create_t4 = false;
    dp_args args2, args3, args4;

    r1 = dp(i + 1, capacity1, capacity2, capacity3);

    if (file_size[i] <= capacity1 && active_threads < MAX_THREADS) {
        args2 = {i + 1, capacity1 - file_size[i], capacity2, capacity3};
        active_threads++;
        pthread_create(&t2, NULL, dp_thread, &args2);
        create_t2 = true;
    } else if (file_size[i] <= capacity1) {
        r2 = dp(i + 1, capacity1 - file_size[i], capacity2, capacity3) + file_size[i];
    }

    if (file_size[i] <= capacity2 && active_threads < MAX_THREADS) {
        args3 = {i + 1, capacity1, capacity2 - file_size[i], capacity3};
        active_threads++;
        pthread_create(&t3, NULL, dp_thread, &args3);
        create_t3 = true;
    } else if (file_size[i] <= capacity2) {
        r3 = dp(i + 1, capacity1, capacity2 - file_size[i], capacity3) + file_size[i];
    }

    if (file_size[i] <= capacity3 && active_threads < MAX_THREADS) {
        args4 = {i + 1, capacity1, capacity2, capacity3 - file_size[i]};
        active_threads++;
        pthread_create(&t4, NULL, dp_thread, &args4);
        create_t4 = true;
    } else if (file_size[i] <= capacity3) {
        r4 = dp(i + 1, capacity1, capacity2, capacity3 - file_size[i]) + file_size[i];
    }

    if (create_t2) {
        void* res2;
        pthread_join(t2, &res2);
        r2 = (intptr_t) res2 + file_size[i];
    }

    if (create_t3) {
        void* res3;
        pthread_join(t3, &res3);
        r3 = (intptr_t) res3 + file_size[i];
    }

    if (create_t4) {
        void* res4;
        pthread_join(t4, &res4);
        r4 = (intptr_t) res4 + file_size[i];
    }

    int result = max(r1, max(r2, max(r3, r4)));

    pthread_mutex_lock(&memo_mutex);
    memo[i][capacity1][capacity2][capacity3] = result;
    pthread_mutex_unlock(&memo_mutex);

    return result;
}

int main() {
    maratona muito coxa

    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> file_size[i];
    int disks[3] = {0,0,0};
    for(int i = 0; i < k; i++) cin >> disks[i];

    memset(memo, -1, sizeof(memo));
    pthread_mutex_init(&memo_mutex, NULL);

    cout << dp(0, disks[0], disks[1], disks[2]) << '\n';

    pthread_mutex_destroy(&memo_mutex);

    return 0;
}


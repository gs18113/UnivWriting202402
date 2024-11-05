#include "strategies.h"

using namespace std;

vector<Agent> agents;
double mem[2000][2000];
double mem2[2000][2000];

RandomGenerator gen;
int dunbar;
int main(int argc, char* argv[])
{
    dunbar = 150;
    int num_rounds = 10;
    bool variable_loss = false;
    bool save_csv = false;
    bool print_standing = false;
    int resource_var = 0;
    for(int i=1;i<argc;i++){
        if(i+1 < argc && strcmp(argv[i], "-n") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-A") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 0));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-B") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 1));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-C") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 2));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-D") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 3));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-E") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 4));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-F") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 5));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-G") == 0){
            int n = atoi(argv[i+1]);
            for(int j=0;j<n;j++){
                agents.push_back(Agent(&gen, 6));
            }
        }
        if(i+1 < argc && strcmp(argv[i], "-var") == 0){
            resource_var = atoi(argv[i+1]);
        }
        if(strcmp(argv[i], "-rounds") == 0){
            num_rounds = atoi(argv[i+1]);
        }
        if(strcmp(argv[i], "-dunbar") == 0){
            dunbar = atoi(argv[i+1]);
        }
        if(strcmp(argv[i], "-var_loss") == 0){
            variable_loss = true;
        }
        if(strcmp(argv[i], "-save_csv") == 0){
            save_csv = true;
        }
        if(strcmp(argv[i], "-print_standing") == 0){
            print_standing = true;
        }
    }
    if(!print_standing) cout << "Rounds: " << num_rounds << ", "
         << "Dunbar num: " << dunbar << ", "
         << "Variable loss: " << variable_loss << ", "
         << "Total agent num: " << agents.size() << ", "
         << "Save csv: " << save_csv << ","
         << "Resource variation: " << resource_var << endl;

    // set up neighbors
    for(int i=0;i<agents.size();i++){
        for(int j=0;j<dunbar;j++){
            int t = gen.getInt(0, agents.size()-1);
            if(i==t){j--;continue;}
            agents[i].neighbors.emplace_back(t);
        }
    }
    // initialize memory with random
    for(int i=0;i<agents.size();i++) for(int j=0;j<agents.size();j++) mem[i][j] = max(gen.getGaussianNumber() / 10 + 0.5, 0.0);
    // simulation
    if(save_csv){
        freopen("output.csv", "w", stdout);
        printf("sigma,Round,Id,Resource,Loss,Strategy\n");
    }
    for(int i=0;i<num_rounds;i++){
        // a round of helping
        for(int j=0;j<agents.size();j++){
            for(int k=0;k<agents.size();k++) mem2[j][k] = mem[j][k] * 0.5;
            for(auto &k : agents[j].neighbors){
                if(variable_loss) agents[j].loss = 1 + gen.getGaussianNumber() / 10;
                // help
                double help = agents[j].strategy(&agents[j], &agents[k], mem[j][k], mem[k][j]);
                //mem2[j][k] = (i * mem[j][k] + help) / (i+1);
                mem2[j][k] += help * 0.5;
            }
        }

        vector<pair<double, int>> v(agents.size());
        for(int j=0;j<agents.size();j++){

            //agents[j].resource = max(agents[j].resource + gen.getGaussianNumber() * 50 , 0.0);
            //agents[j].resource = agents[j]._resource * max(gen.getGaussianNumber() / 10 + 1.01, 0.0);
            agents[j].resource = max(agents[j]._resource + gen.getGaussianNumber() * resource_var, 0.0);
            agents[j]._resource = agents[j].resource;

            for(int k=0;k<agents.size();k++){
                mem[j][k] = mem2[j][k];
                v[k] = {mem[j][k] * mem2[k][j], k};
            }
            // sort v in reverse order
            sort(v.begin(), v.end(), greater<pair<double, int>>());
            int t = 0, k=0;
            for(k=0;k<dunbar*0.9;k++){
                if(v[t].second == j) t++;
                agents[j].neighbors[k] = v[t++].second;
            }
            for(;k<dunbar;k++){
                agents[j].neighbors[k] = gen.getInt(0, agents.size()-1);
            }
            
            if(save_csv)
                printf("%d,%d,%d,%lf,%lf,%c\n", resource_var, i, j, agents[j].resource, agents[j].loss, agents[j].strategy_type + 'A');
        }
    }

    if(print_standing){
        // get final resource per agent and print statistics per strategy

        vector<pair<int, int> > res;

        for (const auto& agent : agents) {
            res.emplace_back(agent.resource, agent.strategy_type);
        }
        sort(res.begin(), res.end(), greater<pair<int, int>>());
        
        for(auto &[r, s] : res) printf("%c ", s+'A');
        printf("\n");

    }

}
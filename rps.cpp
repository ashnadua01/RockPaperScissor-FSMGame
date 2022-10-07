#include<bits/stdc++.h>
using namespace std;

int OutputDFAIndex = 0;

struct DFA{
    char state;
    int r;
    int p;
    int s;
    int index;
};

struct graphNode{
    int state;
    int index;
    struct graphNode* rock;
    int rockGo;
    struct graphNode* paper;
    int paperGo;
    struct graphNode* scissor;
    int scissorGo;
};

vector<struct DFA> inputDfa;
vector<struct graphNode*> outputDFA;
set<vector<int>> globalSetIndex;
map<vector<int>, struct graphNode*> myMap;
void dfs(struct graphNode* node, vector<int> nodeSet);

struct graphNode* makeNode(int index, int state){
    struct graphNode* newNode;
    newNode = (struct graphNode*)malloc(sizeof(struct graphNode));
    newNode->index = index;
    newNode->state = state;
    newNode->rock = NULL;
    newNode->paper = NULL;
    newNode->scissor = NULL;
    newNode->rockGo = -1;
    newNode->paperGo = -1;
    newNode->scissorGo = -1;
    return newNode;
}

int maxChecker(int countRock, int countPaper, int countScissor){
    // 0 for rock, 1 for paper and 2 for scissor
    int initialState = 0;
    if(countScissor >= countRock && countScissor >= countPaper){
        initialState = 0;
    }
    else if(countRock >= countPaper && countRock >= countScissor){
        initialState = 1;
    }
    else if(countPaper >= countRock && countPaper >= countScissor){
        initialState = 2;
    }
    return initialState;
}

int findState(){
    int countRock = 0;
    int countPaper = 0;
    int countScissor = 0;
    for(int i=0; i<inputDfa.size(); i++){
        if(inputDfa[i].state == 'R'){
            countRock++;
        }
        else if(inputDfa[i].state == 'P'){
            countPaper++;
        }
        else if(inputDfa[i].state == 'S'){
            countScissor++;
        }
    }
    return maxChecker(countRock, countPaper, countScissor);
}

int calcMaxState(vector<char> vec){
    int countR = 0;
    int countP = 0;
    int countS = 0;
    for(int i=0; i<vec.size(); i++){
        if(vec[i] == 'R'){
            countR++;
        }
        else if(vec[i] == 'P'){
            countP++;
        }
        else if(vec[i] == 'S'){
            countS++;
        }
    }
    return maxChecker(countR, countP, countS);
}

void rockChecker(struct graphNode* node, vector<int> nodeSet){
    vector<int> rockSet;
    vector<char> rockVector;
    int check = 0;
    int counter = 0;
    for(int i=0; i<inputDfa.size(); i++){
        auto iter = find(nodeSet.begin(), nodeSet.end(), inputDfa[i].index);
        if(iter != nodeSet.end()){
            if(inputDfa[i].state == 'R'){
                check = 1;
                if(node->state == 0){
                    rockSet.push_back(inputDfa[i].r);
                    rockVector.push_back(inputDfa[inputDfa[i].r - 1].state);
                }
                else if(node->state == 1){
                    rockSet.push_back(inputDfa[i].p);
                    rockVector.push_back(inputDfa[inputDfa[i].p - 1].state);
                }
                else if(node->state == 2){
                    rockSet.push_back(inputDfa[i].s);
                    rockVector.push_back(inputDfa[inputDfa[i].s - 1].state);
                }
            }
            else{
                counter++;
            }
        }
    }
    if(counter == nodeSet.size()){
        node->rock = NULL;
        node->rockGo = node->index;
    }
    else{
        int rck = calcMaxState(rockVector);
        sort(rockSet.begin(), rockSet.end());
        if(globalSetIndex.find(rockSet) == globalSetIndex.end()){
            globalSetIndex.insert(rockSet);
            OutputDFAIndex++;
            struct graphNode* newNode;
            newNode = makeNode(OutputDFAIndex, rck);
            node->rock = newNode;
            node->rockGo = OutputDFAIndex;
            outputDFA.push_back(newNode);
            myMap[rockSet] = newNode;
            dfs(newNode, rockSet);
        }
        else{
            struct graphNode* repeatedNode;
            repeatedNode = myMap[rockSet];
            node->rock = repeatedNode;
            node->rockGo = repeatedNode->index;
        }
    }
}

void paperChecker(struct graphNode* node, vector<int> nodeSet){
    vector<int> paperSet;
    vector<char> paperVector;
    int check = 0;
    int counter = 0;
    for(int i=0; i<inputDfa.size(); i++){
        auto iter = find(nodeSet.begin(), nodeSet.end(), inputDfa[i].index);
        if(iter != nodeSet.end()){
            if(inputDfa[i].state == 'P'){
                check = 1;
                if(node->state == 0){
                    paperSet.push_back(inputDfa[i].r);
                    paperVector.push_back(inputDfa[inputDfa[i].r - 1].state);
                }
                else if(node->state == 1){
                    paperSet.push_back(inputDfa[i].p);
                    paperVector.push_back(inputDfa[inputDfa[i].p - 1].state);
                }
                else if(node->state == 2){
                    paperSet.push_back(inputDfa[i].s);
                    paperVector.push_back(inputDfa[inputDfa[i].s - 1].state);
                }
            }
            else{
                counter++;
            }
        }
    }
    if(counter == nodeSet.size()){
        node->paper = NULL;
        node->paperGo = node->index;
    }
    else{
        int ppr = calcMaxState(paperVector);
        sort(paperSet.begin(), paperSet.end());
        if(globalSetIndex.find(paperSet) == globalSetIndex.end()){
            globalSetIndex.insert(paperSet);
            OutputDFAIndex++;
            struct graphNode* newNode;
            newNode = makeNode(OutputDFAIndex, ppr);
            node->paper = newNode;
            node->paperGo = OutputDFAIndex;
            outputDFA.push_back(newNode);
            myMap[paperSet] = newNode;
            dfs(newNode, paperSet);
        }
        else{
            struct graphNode* repeatedNode;
            repeatedNode = myMap[paperSet];
            node->paper = repeatedNode;
            node->paperGo = repeatedNode->index;
        }
    }
}

void scissorChecker(struct graphNode* node, vector<int> nodeSet){
    vector<int> scissorSet;
    vector<char> scissorVector;
    int check = 0;
    int counter = 0;
    for(int i=0; i<inputDfa.size(); i++){
        auto iter = find(nodeSet.begin(), nodeSet.end(), inputDfa[i].index);
        if(iter != nodeSet.end()){
            if(inputDfa[i].state == 'S'){
                check = 1;
                if(node->state == 0){
                    scissorSet.push_back(inputDfa[i].r);
                    scissorVector.push_back(inputDfa[inputDfa[i].r - 1].state);
                }
                else if(node->state == 1){
                    scissorSet.push_back(inputDfa[i].p);
                    scissorVector.push_back(inputDfa[inputDfa[i].p - 1].state);
                }
                else if(node->state == 2){
                    scissorSet.push_back(inputDfa[i].s);
                    scissorVector.push_back(inputDfa[inputDfa[i].s - 1].state);
                }
            }
            else{
                counter++;
            }
        }
    }
    if(counter == nodeSet.size()){
        node->scissor = NULL;
        node->scissorGo = node->index;
    }
    else{
        int ssr = calcMaxState(scissorVector);
        sort(scissorSet.begin(), scissorSet.end());
        if(globalSetIndex.find(scissorSet) == globalSetIndex.end()){
            globalSetIndex.insert(scissorSet);
            OutputDFAIndex++;
            struct graphNode* newNode;
            newNode = makeNode(OutputDFAIndex, ssr);
            node->scissor = newNode;
            node->scissorGo = OutputDFAIndex;
            outputDFA.push_back(newNode);
            myMap[scissorSet] = newNode;
            dfs(newNode, scissorSet);
        }
        else{
            struct graphNode* repeatedNode;
            repeatedNode = myMap[scissorSet];
            node->scissor = repeatedNode;
            node->scissorGo = repeatedNode->index;
        }
    }
}

void dfs(struct graphNode* node, vector<int> nodeSet){
    rockChecker(node, nodeSet);
    paperChecker(node, nodeSet);
    scissorChecker(node, nodeSet);
}

int main(){
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        char c;
        int rock, paper, scissor;
        cin>>c>>rock>>paper>>scissor;
        struct DFA input;
        input.state = c;
        input.r = rock;
        input.p = paper;
        input.s = scissor;
        input.index = i + 1;
        inputDfa.push_back(input);
    }

    int initialState = findState();
    struct graphNode* initialNode;
    vector<int> initialSet;
    for(int i=1; i<n+1; i++){
        initialSet.push_back(i);
    }
    OutputDFAIndex++;
    initialNode = makeNode(OutputDFAIndex, initialState);
    globalSetIndex.insert(initialSet);
    myMap[initialSet] = initialNode;
    outputDFA.push_back(initialNode);
    dfs(initialNode, initialSet); 
    cout<<outputDFA.size()<<endl;

    for(int i=0; i<outputDFA.size(); i++){
        if(outputDFA[i]->state == 0){
            cout<<"R ";
        }
        else if(outputDFA[i]->state == 1){
            cout<<"P ";
        }
        else if(outputDFA[i]->state == 2){
            cout<<"S ";
        }
        cout<<outputDFA[i]->rockGo<<" "<<outputDFA[i]->paperGo<<" "<<outputDFA[i]->scissorGo<<endl;
    }
    return 0;
}
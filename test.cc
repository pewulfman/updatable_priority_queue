
#include "updatable_priority_queue.cc"
#include <iostream>
#include <vector>

using namespace std;
typedef pewulfman::updatable_priority_queue<string,int> upq;

int main(){

    upq q;
    cout << "Test 1" << endl;
    q.push({"Thomas",100});
    q.push({"Pop",0});
    q.push({"Alfred",300});
    q.push({"Batman",10000});
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();

    cout << endl << "Test 2" << endl;
    q.push({"Thomas",100});
    q.push({"Pop",0});
    q.push({"Alfred",300});
    q.push({"Batman",10000});

    q.update_priority("Pop",50000);
    cout << "update Pop to 50000" << endl;
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();


    cout << endl << "Test 3" << endl;
    q.push({"Batman",10000});
    q.push({"Alfred",300});
    q.push({"Thomas",100});
    q.push({"Pop",50000});
    
    q.update_priority("Pop",0);
    cout << "update Pop to 0" << endl;

    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    cout << q.top().first << ", "<< q.top().second << endl;
    q.pop();
    return 0;
}

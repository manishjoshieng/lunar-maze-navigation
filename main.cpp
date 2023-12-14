#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <unordered_set>
#include <memory>
using namespace std;


struct location{
    int x;
    int y;

    location(int a,int b):x(a),y(b){}
    bool operator==(const location& other) const{
        if (x==other.x and y==other.y) return true;
        return false;
    }

    static int distance(const location& a,const location& b){
        return abs(a.x-b.x) + abs(a.y-b.y);
    }

    friend ostream& operator << (ostream& out, const location& loc){
        out<<"{"<<loc.x<< " "<<loc.y<<"}";
        return out;
    }
};


struct QueueNode{
    location loc;
    shared_ptr<QueueNode> parent;
    int current_dist;
    int dist_from_cat;
    int dist_from_target;

    bool operator < (const QueueNode& other) const{
        
        if (dist_from_cat == other.dist_from_cat){
            auto dist1 = current_dist;
            auto dist2 = other.current_dist;
            return dist1 > dist2 ;
        } else {
            return dist_from_cat < other.dist_from_cat;
        }
    }

    QueueNode(location loc, int dist, const location& cat,const location& end, const shared_ptr<QueueNode>& parent) :
        loc(loc),parent(parent), current_dist(dist),
        dist_from_cat(parent ? std::min(location::distance(loc,cat), parent->dist_from_cat): location::distance(loc,cat)),
        dist_from_target(location::distance(loc,end))
    {}

};

namespace std{
    template<>
    struct hash<location>{
        size_t operator()(const location& loc)const{
            auto loc_String = to_string(loc.x) + " "+to_string(loc.y);
            return hash<string>{}(loc_String); 
        }
    };
}

list<location> BuildPath(const shared_ptr<QueueNode>& node){
    list<location> path;
    auto cur = node;
    while(cur){
        path.push_front(cur->loc);
        cur = cur->parent;
    }
    return path;
}

vector<int> dir_x = {0,0,1,-1};
vector<int> dir_y = {1,-1,0,0};

list<location> 
findShortestPath(int max_row,int max_col, location& cat, location& start, location& end){
    if(max_row == 0 || max_col==0) return list<location>();
    shared_ptr<QueueNode> startNode(new QueueNode(start,0,cat,end,nullptr));
    auto comparator = [](const std::shared_ptr<QueueNode>& a, const std::shared_ptr<QueueNode>& b) {
        return *a < *b;  
    };

    std::priority_queue<std::shared_ptr<QueueNode>, std::vector<std::shared_ptr<QueueNode>>, decltype(comparator)> q(comparator);

    q.push(startNode);
    unordered_set<location> visited;

    while(!q.empty()){
        auto cNode = q.top();q.pop();
        if (cNode->loc == end){
            return BuildPath(cNode);
        }
        visited.emplace(cNode->loc);
        for(int i=0;i<dir_x.size();i++){
            location cur = cNode->loc;
            location next(cur.x+dir_x[i],cur.y+dir_y[i]);
            if(next.x >= max_row || 
                next.x<0 || 
                next.y >= max_col || 
                next.y <0 || 
                next==cat || 
                visited.find(next)!=visited.end())
            {
                continue;
            }
            shared_ptr<QueueNode> nNode(new QueueNode(next,cNode->current_dist+1,cat,end,cNode));
            q.push(nNode);
        }
    }
    return list<location>();
}

int main() {
    int max_row = 6;
    int max_col = 6;

    location start(0,0);
    location end(5,5);
    location cat(2,2);

    auto path = findShortestPath(max_row,max_col,cat,start,end);

    for(auto p :path){
        cout<<p<<" ";
    }
}

#include <iostream>
#include <fstream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/graphviz.hpp>
#include <queue>
#include <stdio.h>
typedef boost::property<boost::vertex_distance_t, double> VertexProperty;
typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty,EdgeWeightProperty> Graph;
typedef boost::graph_traits < Graph >::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits < Graph >::vertex_iterator vertex_iterator;
typedef boost::graph_traits < Graph >::adjacency_iterator adjacency_iterator;
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
Graph g;
std::map<std::vector<int>,std::pair<std::pair<int,int>,int> > li;
int m = 6;
int balance(std::vector<int> p,std::vector<int> l);
int isbalance()
{
	std::vector<int> s;
	std::vector<std::vector<int> > l;
	int i,j,k;
	for(i=0;i<6;i++)
	{	
		for(j=0;j<6;j++)
		{	k = 0;
			if(i!=j)
			{		
		for(std::map<std::vector<int>,std::pair<std::pair<int,int>,int> > ::const_iterator it = li.begin(); it != li.end(); it++)
				{
					std::pair<std::pair<int,int>,int> key = it->second;
					std::pair<int,int> key2 = key.first;
					int p = key.second;
					std::vector<int> key1 = it->first;
					if(i==key2.first && j ==key2.second)
					{
						k++;
						s.push_back(p);
						l.push_back(key1);
						if(k>1){
						int p = s.back();
						std::vector<int> h = l.back();
						s.pop_back();
						l.pop_back();
						if(p!=s.back()){
						std::cout<< "not balanced between vertices" <<" " << i << " " << j <<std::endl;
						balance(l.back(),h);
						break;							
							}
						}
					}		
				}
			}
		}
	}
return 1;
}
bool isadjacency_node_not_present_in_current_path(int node,std::vector<int>path)
{
    for(int i=0;i<path.size();++i)
    {
        if(path[i]==node)
        return false;
    }
    return true;
}

int findpath(int source,int target)
{
	IndexMap index = get(boost::vertex_index, g);
	std::vector<int> path;
	path.push_back(source);
	std::queue<std::vector<int> >q;
	q.push(path);
	
	while(!q.empty())
    	{
        	path=q.front();
        	q.pop();

        	int last_nodeof_path=path[path.size()-1];
        	if(last_nodeof_path==target)
        	{	
			int t = -1;
            		std::cout<<"The Required path is:: ";
            		std::cout<<"[ ";
    			for(int i=0;i<path.size();++i)
    				{
        				std::cout<<path[i]<<" ";
					t++;
    				}
    					std::cout<<"]"<<std::endl;
					std::cout<< t <<std::endl;
					li.insert(std::make_pair(path,std::make_pair(std::make_pair(source,target),t)));
					
		}
	
	std::pair<adjacency_iterator, adjacency_iterator> neighbors = boost::adjacent_vertices(vertex(last_nodeof_path,g), g);
        for(; neighbors.first != neighbors.second; ++neighbors.first)
        {		
            if(isadjacency_node_not_present_in_current_path(index[*neighbors.first],path))
            {

                std::vector<int>new_path(path.begin(),path.end());
                new_path.push_back(index[*neighbors.first]);
                q.push(new_path);
            }
        }
    }
    return 0;
}

int balance(std::vector<int> p,std::vector<int> l){
	int a = p.size();
	int b = l.size();
	int i;	
	std::cout<< a <<std::endl;
	std::cout<< b <<std::endl;
	for( i = 0;i!=a && i!=b;i++){
		if(p[i]!=l[i]){
		break;
		}
	}
	
	if(a>b){
	int j = a-b;
	while(j--){
		boost::add_vertex(g);
		boost::add_edge(l[i-1],m,g);
		boost::add_edge(m,l[i],g);
		remove_edge(l[i-1],l[i],g);
		m++;
	}
	}
	else{
	int j = b-a;
	while(j--){
		boost::add_vertex(g);
	}
	}	
}


int main(int argc, char*argv[])
{
 if(argc < 2)
  {
    std::cerr << "Required: filename.dot" << std::endl;
    return -1;
  }
  std::string filename = argv[1];
  std::ofstream fout(filename.c_str());
 
// Create two edges
  boost::add_edge(0,1,1,g);
  boost::add_edge(1,2,2,g);
  boost::add_edge(1,3,3,g);
  boost::add_edge(3,5,4,g);
  boost::add_edge(2,4,5,g);
  boost::add_edge(4,5,5,g);
int p1,p2,p3,p4;
IndexMap index = get(boost::vertex_index, g);
vertex_iterator vi,vi_end,v,v_end,e,e_end,ei,ei_end,target,source;						
for(tie(vi,vi_end)=vertices(g);vi!=vi_end;vi++)
	{
		for(tie(v,v_end)=vertices(g);v!=v_end;v++)
			{	if(index(*vi)!=index(*v))
					{
						findpath(index(*vi),index(*v));
					}
			}

	}
		isbalance();
	
	write_graphviz(fout,g);
 }

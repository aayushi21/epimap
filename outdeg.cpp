#include <iostream>
#include <fstream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/graphviz.hpp>

typedef boost::property<boost::vertex_distance_t, double> VertexProperty;
typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperty,EdgeWeightProperty> Graph;
typedef boost::graph_traits < Graph >::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits < Graph >::vertex_iterator vertex_iterator;
typedef boost::graph_traits < Graph >::edge_iterator edge_iterator;
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
typedef boost::graph_traits<Graph>::degree_size_type degree_size_type;
Graph g;
int m =6;
void balance_outdeg(int a,int b){
	m++;
	boost::add_vertex(g);
	edge_iterator e,e_end;
	IndexMap index = get(boost::vertex_index, g);
	for(tie(e,e_end)=edges(g);e!=e_end;++e){
	if(a==index[source(*e,g)] && b!=0){
		b--;
		int x = index[target(*e,g)];
		int y = index[source(*e,g)];
			boost::add_edge(m,x,g);
			remove_edge(y,x,g);
		}
	if(a==index[target(*e,g)]){
		int x = index[source(*e,g)];
			boost::add_edge(x,m,g);
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
 
  std::string filename1 = argv[2];
  std::ofstream fout1(filename1.c_str());

// Create two edges
  boost::add_edge(0,1,1,g);
  boost::add_edge(1,2,2,g);
  boost::add_edge(2,3,3,g);
  boost::add_edge(2,4,4,g);
  boost::add_edge(2,5,5,g);
  boost::add_edge(2,6,5,g);
//writing the graph to file	
  write_graphviz(fout1,g);
  int res=2;
  degree_size_type out;
  IndexMap index = get(boost::vertex_index, g);
  vertex_iterator vi,vi_end,v,v_end,e,e_end,ei,ei_end,target,source;						
  for(tie(vi,vi_end)=vertices(g);vi!=vi_end;vi++)
	{
		out = out_degree(*vi,g);
		//condition where outdegree is greater than resources
		if(out > res ){
		int diff = out-res;
		//if satisfied then balance function called
		balance_outdeg(index(*vi),diff);
		tie(vi,vi_end)=vertices(g);
		}
	}
	
	write_graphviz(fout,g);
 }

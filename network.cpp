#include "network.h"
#include "iostream"
#include <algorithm>

void Network::resize(const size_t& n){
	values.clear();
	links.clear();
	RandomNumbers r;
	for(size_t i(0); i< n ; ++i){
		values.push_back(r.normal(0, 1));
	}
}




 bool Network::add_link(const size_t& a, const size_t& b){  //comment tester que la valeur a bien été rajoutée?
	 if(a==b){
		 return false;
	 }
	 
	 if(a>=values.size() or b>=values.size())
	 {
		 return false;
	 }
		 
	 std::vector<size_t> neighborsA(a); //tous les voisins de a
	 std::vector<size_t> neighborsB(b); //tpus les voisins de b
	 
	 if(std::find(neighborsA.begin(), neighborsA.end(), b)==neighborsA.end())
	 {  
	  links.insert(std::make_pair(a,b));
	  links.insert(std::make_pair(b,a));
	  return true;
     }
	  return false;
}
	 
 
 
 
 size_t Network::random_connect(const double& mean_deg){
	 links.clear();
	 
	 int nb;
	 size_t links_created (0);
	 
	 for(size_t i(0); i<values.size() ; ++i){         
		                                   
		 int degre(RNG.poisson(mean_deg));   
		 nb=0;                                 
		
			
			 while(nb<degre and degre<values.size()){   
				int b=RNG.uniform_double( 0, values.size()-1);       
				if(add_link(i, b)){
				 ++nb;
				 ++links_created;
				 
				}
		     }
		 
	 }
	 
		 
	return links_created; //que retourne cette fonction???
	
 }
 
 size_t Network::set_values(const std::vector<double>& v){
	 
	 values.clear();
	 links.clear();
	 
	 for( size_t i(0); i<v.size() ; ++i){
		 values.push_back(v[i]);
		 
	 }
	 return values.size();
 }
 
 
 size_t Network::size() const{
	 return values.size();
 }
 
 
 size_t Network::degree(const size_t& n) const{
	 return links.count(n);           //compte le nombre de valeur ayant pour clé n;
 }
 
 
double Network::value(const size_t& n) const{
	   return values[n];
   }
   
std::vector<double> Network::sorted_values() const{
	std::vector<double> output;
	
	for(size_t  i(0); i<values.size() ; ++i){
		output.push_back(values[i]);
	}
		
	 std::sort(output.begin(), output.end(), std::greater<double>());
	 
 
 return output;
}
 
std::vector<size_t> Network::neighbors(const size_t& n) const{
	std::vector<size_t> output;
	output.clear();
	auto range = links.equal_range(n);
	
	if(n<=values.size()){
	
	for (auto it = range.first; it != range.second; ++it){
		output.push_back(it->second);
		
     }
     }
  return output;

}
	

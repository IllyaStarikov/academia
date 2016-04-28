//
//  CloseCent.cpp
//  Source Code
//
//  Created by Timothy Ott on 4/27/16.
//  Copyright © 2016 Timothy Ott. All rights reserved.
//

#include "CloseCent.hpp"

void CloseCent(const VectArray & input){
    vector<double> Close;
    vector<int> High1;
    vector<int> High2;
    vector<int> High3;
    vector<int> High4;
    double High1Val = 0;
    double High2Val = 0;
    double High3Val = 0;
    double High4Val = 0;
    int sum = 0;
    for (auto const &vertex : input){
      for (auto const &edge : vertex){
        sum += edge;
      }
      Close[vertex] = 1.0/sum;
      if (Close[vertex] == High1Val)
         High1.push_back(vertex);
      else if (Close[vertex] == High2Val)
         High2.push_back(vertex);
      else if (Close[vertex] == High3Val)
        High3.push_back(vertex);
      else if (Close[vertex] == High4Val)
        High4.push_back(vertex);
      else if (Close[vertex] > High1Val){
         High4 = High3;
         High4Val = High3Val;
         High3 = High2;
         High3Val = High2Val;
         High2 = High1;
         High2Val = High1Val;
         High1Val = Close[vertex];
         High1.clear();
         High1.push_back(vertex);
      }
      else if (Close[vertex] > High2Val){
         High4 = High3;
         High4Val = High3Val;
         High3 = High2;
         High3Val = High2Val;
         High2Val = Close[vertex];
         High2.clear();
         High2.push_back(vertex);
      }
      else if (Close[vertex] > High3Val){
         High4 = High3;
         High4Val = High3Val;
         High3Val = Close[vertex];
         High3.clear();
         High3.push_back(vertex);
      }
      else if (Close[vertex > High4Val){
        High4Val = Close[vertex];
        High4.clear();
        High4.push_back(vertex);
      }
      sum = 0;
    }
    std::cout<<"Highest Closeness Values"<<std::endl;
    std::cout<<"Value: "<<High1Val<<" Vertices: ";
    for (auto const &element : High1){
      cout<<element<<", ";
    }
    cout<<std::endl;
    
    std::cout<<"Value: "<<High2Val<<" Vertices: ";
    for (auto const &element : High2){
      cout<<element<<", ";
    }
    cout<<std::endl;

    std::cout<<"Value: "<<High3Val<<" Vertices: ";
    for (auto const &element : High3){
      cout<<element<<", ";
    }
    cout<<std::endl;
    
    std::cout<<"Value: "<<High4Val<<" Vertices: ";
    for (auto const &element : High4){
      cout<<element<<", ";
    }
    std::cout<<std::endl;
    
    CloseGraph(Close);
}

void CloseGraph(const vector<double> & Close){
  auto GraphSol = std::map<double, int>();
  double index;
  
  for (const auto &element : Close){
    index = element;
    GraphSol[index]++;
  }
  
  if (PRINT_SOLUTIONS) {
    for (const auto &element : GraphSol) {
      std::cout << element.first << ": " << element.second << std::endl;
    }
  }
}

void AllCloseCent(VectArray & UWUDshort, VectArray & UWDshort, VectArray & WUDshort, VectArray & WDshort){
  
    if (PRINT_SOLUTIONS) { std::cout << "CLOSENESS CENTRALITY: " << std::endl; }
  
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_UNWEIGHTED_DIRECTED); }
    CloseCent(UWDshort);
    
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_WEIGHTED_DIRECTED); }
    CloseCent(WDshort);
    
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_WEIGHTED_UNDIRECTED); }
    CloseCent(WUDshort);
    
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_UNWEIGHTED_UNDIRECTED); }
    CloseCent(UWUDshort);
  
}
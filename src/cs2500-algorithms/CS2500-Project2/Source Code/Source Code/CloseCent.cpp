//
//  CloseCent.cpp
//  Source Code
//
//  Created by Timothy Ott on 4/27/16.
//  Copyright © 2016 Timothy Ott. All rights reserved.
//

#include "CloseCent.hpp"

#include <limits>

typedef std::numeric_limits< double > dbl;

void CloseCent(const AdjacencyMatrix & input){
    auto Close = std::vector<double>();  //vector to hold the solution set
    std::vector<int> High1;				// these are vectors to hold the vertices that correspond to the "Highest Centrality"
    std::vector<int> High2;
    std::vector<int> High3;
    std::vector<int> High4;

    long double High1Val = 0;     //variables to hold the actual values for the highest value of closeness
    long double High2Val = 0;
    long double High3Val = 0;
    long double High4Val = 0;
    int sum = 0;
    int i = 0;
    for (auto const &vertex : input){			//for each vertex, and each edge in that vertex, add the edge weight to sum.
      for (auto const &edge : vertex){
        sum += edge;
      }

      Close.push_back(1.0/sum);					//push that value into solution set
      if (Close[i] == High1Val)					//checking if it falls into the highest 4.
         High1.push_back(i);
      else if (Close[i] == High2Val)
         High2.push_back(i);
      else if (Close[i] == High3Val)
        High3.push_back(i);
      else if (Close[i] == High4Val)
        High4.push_back(i);
      else if (Close[i] > High1Val){			//checking if it replaces one of the highest 4.
         High4 = High3;
         High4Val = High3Val;
         High3 = High2;
         High3Val = High2Val;
         High2 = High1;
         High2Val = High1Val;
         High1Val = Close[i];
         High1.clear();
         High1.push_back(i);
      }
      else if (Close[i] > High2Val){
         High4 = High3;
         High4Val = High3Val;
         High3 = High2;
         High3Val = High2Val;
         High2Val = Close[i];
         High2.clear();
         High2.push_back(i);
      }
      else if (Close[i] > High3Val){
         High4 = High3;
         High4Val = High3Val;
         High3Val = Close[i];
         High3.clear();
         High3.push_back(i);
      }
      else if (Close[i] > High4Val){
        High4Val = Close[i];
        High4.clear();
        High4.push_back(i);
      }
      sum = 0;									//resetting values for next test
      i++;
    }
    std::cout<<"Highest Closeness Values"<<std::endl;		//outputting results
    std::cout<<"Value: "<<High1Val<<" Vertices: ";
    for (auto const &element : High1){
      std::cout<<element<<", ";
    }
    std::cout<<std::endl;
    
    std::cout<<"Value: "<<High2Val<<" Vertices: ";
    for (auto const &element : High2){
      std::cout<<element<<", ";
    }
    std::cout<<std::endl;

    std::cout<<"Value: "<<High3Val<<" Vertices: ";
    for (auto const &element : High3){
      std::cout<<element<<", ";
    }
    std::cout<<std::endl;
    
    std::cout<<"Value: "<<High4Val<<" Vertices: ";
    for (auto const &element : High4){
      std::cout<<element<<", ";
    }
    std::cout<<std::endl;
    
    CloseGraph(Close);
}

void CloseGraph(std::vector<double> & Close){					//outputting the needed results for the graph
  auto GraphSol = std::map<double, int>();
  double index;
  
  for (const auto &element : Close){
    index = element;
    GraphSol[index]++;
  }
        std::cout.precision(dbl::max_digits10);
    
  if (PRINT_SOLUTIONS) {
    for (const auto &element : GraphSol) {
        std::cout << std::fixed << element.first << ": " << element.second << std::endl;
    }
  }
}

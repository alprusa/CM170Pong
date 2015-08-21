#include <SFML/Graphics.hpp>
#include <iostream>
#include "Net.h"

using namespace std;

net::net(int dashes, int inc, string orientation):numNetDashLines(dashes), yIncrement(inc){
    netShape = sf::VertexArray(sf::Lines, numNetDashLines);
    if(orientation == "vertical"){
    	x = 250;
	    y = 0;
    }
    else{
    	x = 0;
	    y = 250;
    }

    for(int i = 0; i < numNetDashLines; i++){
    	if(orientation == "vertical"){
	        if(i == 0) netShape[i].position = sf::Vector2f(x, y);
	        else netShape[i].position = sf::Vector2f(x, y += yIncrement);
	    }
	    else{
	        if(i == 0) netShape[i].position = sf::Vector2f(x, y);
	        else netShape[i].position = sf::Vector2f(x += yIncrement, y);
	    }
    }
}

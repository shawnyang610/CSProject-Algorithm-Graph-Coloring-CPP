//CS700-34 GRAPH COLORING METHOD 2
//SHAWN YANG

#include <iostream>
#include <fstream>
using namespace std;

class GraphColoring {
public:
    int numNodes;
    int currentNode;
    int newColor;
    int usedColor;
    int ** adjacentcyMatrix;
    ifstream *infile;
    ofstream *outfile;
    
    GraphColoring(int in_numNodes, ifstream *in_infile, ofstream *in_outfile){
        numNodes=in_numNodes;
        infile=in_infile;
        outfile=in_outfile;
        
        adjacentcyMatrix=new int* [numNodes+1];
        for (int i=0; i<numNodes+1; i++){
            adjacentcyMatrix[i]=new int[numNodes+1];
            for (int j=0; j<numNodes+1; j++){
                adjacentcyMatrix[i][j]=0;
            }
        }
        newColor=0;
        usedColor=0;
        currentNode=0;
        
        
    }
    
    void start(){
        loadMatrix();
        do {
            currentNode++;
            printMatrix();
            usedColor = findUsedColor();
            if (usedColor>0) {
                adjacentcyMatrix[currentNode][currentNode]=usedColor;
            }
            else {
                newColor++;
                adjacentcyMatrix[currentNode][currentNode]=newColor;
            }
        } while (!allNodesColored());
        
        printMatrix();
        *outfile<< "number of color used: "<<newColor<<endl;
    }
    
    void loadMatrix(){
        int nodeX;
        int nodeY;
        while (*infile>>nodeX>>nodeY){
            cout<<"loading matrix"<<nodeX<<nodeY<<endl;
            *outfile<< nodeX<<" "<<nodeY<<endl; //print the input edges in pairs.
            adjacentcyMatrix[nodeX][nodeY]=1;
            adjacentcyMatrix[nodeY][nodeX]=1;
        }
        outfile->flush();
    }
    
    void printMatrix(){
        for (int i=1; i<numNodes+1; i++){
            for (int j=1; j<numNodes+1; j++){
                *outfile<<adjacentcyMatrix[i][j]<<"  ";
            }
            *outfile<<endl;
        }
        *outfile<<endl;
        outfile->flush();
    }
    
    int findUsedColor(){
        int foundUsedColor=0;
        int colorChoice=newColor;
        while (colorChoice>0){
            if (checkAdjacent(currentNode, colorChoice)==0){
                foundUsedColor=colorChoice;
                break;
            }
            colorChoice--;
        }
        
        return foundUsedColor;
    }
    
    
    
    
    
    int checkAdjacent(int in_currentNode, int in_currentColor){
        for (int i=1; i<numNodes+1; i++){
            if(adjacentcyMatrix[in_currentNode][i]==1 && adjacentcyMatrix[i][i]==in_currentColor){
                return 1;
            }
        }
        return 0;
    }
    
    
    
    
    
    
    
    
    bool allNodesColored(){
        for (int i=1; i<numNodes+1; i++){
            if(adjacentcyMatrix[i][i]==0)
                return false;
        }
        return true;
    }
    
    
};

class Node {
public:
    int colorID;
    Node *next;
    Node(){
        colorID=0;
        next=NULL;
    }
};

int main(int argc, const char * argv[]) {
    int numNodes;
    ifstream *infile = new ifstream();
    ofstream *outfile = new ofstream();
    if (argc<3){
        cout<<"Please specify input.txt and output.txt and try again"<<endl;
        return 0;
    }
    try {
        infile->open(argv[1]);
        outfile->open(argv[2]);
        *infile>>numNodes;
    } catch (exception *e) {
        cout<<"problem opening files or reading first number"<<e<<endl;
        return 0;
    }
    GraphColoring *graphColoring = new GraphColoring(numNodes, infile, outfile);
    graphColoring->start();
    
    infile->close();
    outfile->close();
    
    
    return 0;
}

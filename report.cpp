#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Posn {
   public:
   double x;
   double y;
   Posn(double x,double y) : x(x), y(y) {}
};

vector<Posn> pairs;

class QuadTree {
  public:
  string direction;
  double xstart;
  double xend;
  double ystart;
  double yend;
  int numpoints;
  QuadTree *NW;
  QuadTree *NE;
  QuadTree *SE;
  QuadTree *SW;
  vector<Posn> quadpoints;
  bool pointInQuad(Posn point) { 
    return (point.x > xstart && point.x <= xend && point.y > ystart && point.y <= yend);
  }
  // Constructor
  QuadTree(string direction) : direction(direction) {
      NW = NULL;
      NE = NULL;
      SE = NULL;
      SW = NULL;
  }     
};

void setPoints(QuadTree *t, double xstart, double xend, double ystart, double yend) {
   t->xstart = xstart; 
   t->xend = xend;
   t->ystart = ystart;
   t->yend = yend;
   for (int i = 0; i < pairs.size(); i++) {
       if (t->pointInQuad(pairs[i])) {
          t->quadpoints.push_back(pairs[i]);
       }
   }
   t->numpoints = t->quadpoints.size();
}

void divide(QuadTree *t) { 
   double xstart, xend, ystart, yend;
   // Same xstart and same yend for NW
   xstart = t->xstart;
   yend = t->yend;
   xend = (t->xend - t->xstart) / 2 + xstart;
   ystart = yend - (yend - t->ystart) / 2 ;
   setPoints(t->NW,xstart,xend,ystart,yend);
   // Same yend and same xend
   xend = t->xend;
   yend = t->yend;
   xstart = xend - ((xend - t->xstart) / 2);
   ystart = yend - ((yend - t->ystart) / 2);
   setPoints(t->NE,xstart,xend,ystart,yend);
   // Same xend and same ystart
   xend = t->xend;
   ystart = t->ystart;
   xstart = xend - (xend - t->xstart) / 2;
   yend = yend - (t->yend - ystart) / 2;
   setPoints(t->SE,xstart,xend,ystart,yend);
   // Same xstart and ystart
   xstart = t->xstart;
   ystart = t->ystart;
   xend = xstart + (t->xend - t->xstart) / 2;
   yend = ystart + (t->yend - t->ystart) / 2;
   setPoints(t->SW,xstart,xend,ystart,yend);
}

void splitTree(QuadTree *t) {
    if (t->quadpoints.size() <= 1) {
       if (t->quadpoints.size() == 1) {
           //cout << "reached t num points == 1" << endl;
           cout << t->quadpoints[0].x << endl << t->quadpoints[0].y << endl;
       }
       // done, it doesnt have any children, theres only one point and you can print it.
       return;
    }
    else {
      //cout << " recursion tyyyyymmmm" << endl;
       // Recurse on each
       t->NW = new QuadTree("NW");
       t->NE = new QuadTree("NE");
       t->SE = new QuadTree("SE");
       t->SW = new QuadTree("SW");
       divide (t);
       splitTree(t->NW);
       splitTree(t->NE);
       splitTree(t->SE);
       splitTree(t->SW);
   }
}
        
int main() {
  int numpairs;
  double xcoor;
  double ycoor;
  cin >> numpairs;
  for (int i = 0; i < numpairs; i++) {
     cin >> xcoor;
     cin >> ycoor;
     Posn p = Posn(xcoor,ycoor);
     pairs.push_back(p);
  }
  // Inital quad tree which has alll the points, need to split it if theres more than one point
  QuadTree *t = new QuadTree("root");
  double xstart = 0;
  double xend = 1;
  double ystart = 0;
  double yend = 1;
  setPoints(t,xstart,xend,ystart,yend);
  splitTree(t);
}


//Title:       MouseApplet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package MouseMove;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class MouseMove extends Applet implements MouseListener,MouseMotionListener{
  boolean isStandalone = false;
  Point startPoint;
  Point points[];
  int numpoints;
  int numclicks;
  boolean drawing;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public MouseMove() {
  }

  //Initialize the applet
  public void init()
  {
    startPoint=new Point(0,0);
    points=new Point[1000];
    numpoints=0;
    numclicks=0;
    drawing=false;
    addMouseListener(this);
    addMouseMotionListener(this);
    setBackground(Color.white);
    setSize(400,300);
  }

  public void paint(Graphics g)
  {
    g.drawString(String.valueOf(numclicks),0,20);
    int oldX=startPoint.x;
    int oldY=startPoint.y;
    for(int x=0;x<numpoints;x++)
    {
      g.drawLine(oldX,oldY,points[x].x,points[x].y);
      oldX=points[x].x;
      oldY=points[x].y;
    }
  }

  public void mouseClicked(MouseEvent e)
  {
  }
  public void mousePressed(MouseEvent e)
  {
    drawing=true;
    startPoint.x=e.getX();
    startPoint.y=e.getY();
    numclicks++;
    repaint();
  }
  public void mouseReleased(MouseEvent e)
  {
  }
  public void mouseExited(MouseEvent e)
  {
  }
  public void mouseEntered(MouseEvent e)
  {
  }
  public void mouseDragged(MouseEvent e)
  {
  }
  public void mouseMoved(MouseEvent e)
  {
    if((drawing) && (numpoints<1000))
    {
      points[numpoints]=new Point(e.getX(),e.getY());
      numpoints++;
      repaint();
    }
  }


  //Component initialization
  private void jbInit() throws Exception {
  }

  //Start the applet
  public void start() {
  }

  //Stop the applet
  public void stop() {
  }

  //Destroy the applet
  public void destroy() {
  }

  //Get Applet information
  public String getAppletInfo() {
    return "Applet Information";
  }

  //Get parameter info
  public String[][] getParameterInfo() {
    return null;
  }
}
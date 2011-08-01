
//Title:       MouseApplet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package mouseapplet;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

// MESSAGES
// 0 = Click
// 1 = IN
// 2 = OUT

public class MouseApplet extends Applet implements MouseListener{
  boolean isStandalone = false;
  int coordx,coordy,msg;
  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public MouseApplet() {
  }

  //Initialize the applet
  public void init()
  {
    coordx=-1;
    coordy=-1;
    msg=-1;
    Font font = new Font("TimesRoman",Font.BOLD,24);
    setFont(font);
    addMouseListener(this);
    setBackground(Color.white);
    setSize(400,300);
  }

  public void paint(Graphics g)
  {
    switch(msg)
    {
      case(1): g.drawString("Mouse in Window",0,100);
                    break;
      case(2):g.drawString("Mouse outside Window",0,100);
                    break;
      case(0): g.drawString("("+  String.valueOf(coordx)+","+
                                          String.valueOf(coordy)+")",
                                          coordx,coordy);
    }
  }

  public void mouseClicked(MouseEvent e)
  {
    coordx=e.getX();
    coordy=e.getY();
    msg=0;
    repaint();
  }
  public void mousePressed(MouseEvent e)
  {
  }
  public void mouseReleased(MouseEvent e)
  {
  }
  public void mouseExited(MouseEvent e)
  {
    msg=2;
    repaint();
  }
  public void mouseEntered(MouseEvent e)
  {
    msg=1;
    repaint();
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
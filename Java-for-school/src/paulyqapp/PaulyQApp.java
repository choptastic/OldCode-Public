
//Title:       PaulyQ App
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package paulyqapp;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class PaulyQApp extends Applet {
  boolean isStandalone = false;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public PaulyQApp() {
  }

  //Initialize the applet
  public void init()
  {
    setBackground(Color.white);
    setSize(320,240);
  }

  public void paint(Graphics g)
  {
    Font f= new Font("TimesRoman",Font.PLAIN,20);
    g.setFont(f);
    g.drawRoundRect(75,20,150,75,20,20);
    g.drawString("Don't Quote Me",85,60);
    g.drawLine(120,150,175,95);
    g.drawOval(70,115,45,45);
    g.drawOval(60,160,65,65);
    g.fillRoundRect(80,125,8,15,7,10);
    g.fillRoundRect(95,123,8,15,7,10);
    g.drawArc(80,140,22,15,160,235);

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

  public static void main(String args[])
  {
    PaulyQApp app=new PaulyQApp();
    Frame f = new Frame("Quotation Window");
    app.init();
    app.start();
    f.add("Center",app);
    f.setSize(410,300);
    f.show();
  }
}
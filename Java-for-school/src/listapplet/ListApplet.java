
//Title:
//Version:     1.0
//Copyright:   Copyright (c)
//Author:
//Company:
//Description:
package listapplet;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class ListApplet extends Applet implements ItemListener{
  boolean isStandalone = false;

  List companyList;
  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public ListApplet() {
  }

  //Initialize the applet
  public void init()
  {
    companyList=new List(5,true); // set to true for multivalues
    companyList.add("Sun");
    companyList.add("Misrosoft");
    companyList.add("Compaq");
    companyList.add("Johnson Controls");
    companyList.add("Allen Bradly");
    companyList.add("Texas Instruments");
    companyList.add("Packard Bell");
    companyList.add("Toshiba");
    companyList.add("Sony");
    companyList.add("Dell");
    add(companyList);
    companyList.addItemListener(this);
    companyList.setBackground(Color.yellow);
    companyList.setForeground(Color.gray);
    try
    {
      jbInit();
    }
    catch(Exception e)
    {
      e.printStackTrace();
    }
  }

  public void itemStateChanged(ItemEvent e) // modified from ActionListener
  {
    repaint();
  }

  public void paint(Graphics g)
  {
    String s="";
    int i,y=0; // i is a counter, y is the vertical position counter
    g.drawString("Chosen Items:",100,110);
    for(i=0;i<companyList.getItemCount();i++) // for all items in list
      if(companyList.isIndexSelected(i)) // if item is selected
      {
                  //display company at location based on y value
        g.drawString(companyList.getItem(i),100,y*13+130); // display name
        y++;  // increment y (line value)
      }
    if(y==0) // if none selecte, display "None"
      g.drawString("None",100,130);
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
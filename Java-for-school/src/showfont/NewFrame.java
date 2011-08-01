
/**
 * Title:        Show Fonts Applet<p>
 * Description:  <p>
 * Copyright:    Copyright (c) Jesse Gumm<p>
 * Company:      <p>
 * @author Jesse Gumm
 * @version 1.0
 */
package showfont;

import java.awt.Frame;
import java.awt.*;
import java.awt.event.*;

public class NewFrame extends Frame implements ActionListener
{
  Font fnt = new Font("TimesRoman",Font.BOLD,25);
  String label="TimesRoman";
  Color c = Color.black;

  public NewFrame(String title)
  {
    super(title);
  }

  public void actionPerformed(ActionEvent evt)
  {
    MenuItem selectitem =(MenuItem)evt.getSource();
    if(selectitem.getLabel()=="TimesRoman")
      label = selectitem.getLabel();
    else if(selectitem.getLabel()=="Arial")
      label=selectitem.getLabel();
    else if (selectitem.getLabel()=="Courier")
      label=selectitem.getLabel();
    fnt= new Font(label,Font.BOLD,25);

    if(selectitem.getLabel()=="Green")
      c=Color.green;
    else if(selectitem.getLabel()=="Black")
      c=Color.black;
    else if(selectitem.getLabel()=="Red")
      c=Color.red;
    repaint();
  }

  public void paint(Graphics g)
  {
    g.setFont(fnt);
    g.setColor(c);
    g.drawString("This is the " + label + " selected by You",30,80);
  }

  public NewFrame() {
  }
}
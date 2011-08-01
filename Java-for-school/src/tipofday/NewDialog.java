
/**
 * Title:        New Dialog from Tip applet
 * Description:
 * Copyright:    Copyright (c) <p>
 * Company:      <
 * @author        Jesse Gumm
 * @version 1.0
 */
package tipofday;

import java.awt.Dialog;
import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class NewDialog extends Dialog implements ActionListener
{
  public NewDialog(Frame f,String title, boolean m)
  {
    super(f,title,m);
  }

  public void actionPerformed(ActionEvent e)
  {
    if(e.getSource() instanceof Button)
    {
      Button b = (Button)e.getSource();
      if(b.getLabel().equals("OK"))
        this.dispose();
      else if(b.getLabel().equals("Open"))
      {
        Frame w = new Frame();
        NewDialog g=new NewDialog(w,"Another Window",false);
        g.setLayout(new GridLayout(2,1,10,1));
        g.setSize(100,100);
        g.show();
      }
    }
  }
}
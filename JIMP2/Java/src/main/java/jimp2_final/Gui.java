package jimp2_final;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class Gui extends javax.swing.JFrame{

    /**
     * Creates new form Gui
     */
    public Gui() {
        initComponents();
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        input_path = new javax.swing.JTextField();
        output_path = new javax.swing.JTextField();
        get_input_path = new javax.swing.JButton();
        get_output_path = new javax.swing.JButton();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        odbicia = new javax.swing.JCheckBox();
        n_o_cykle = new javax.swing.JSpinner();
        jLabel1 = new javax.swing.JLabel();
        jSeparator2 = new javax.swing.JSeparator();
        jPanel3 = new javax.swing.JPanel();
        start_run = new javax.swing.JButton();
        IMG_load = new javax.swing.JPanel();
        load_label = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowActivated(java.awt.event.WindowEvent evt) {
                formWindowActivated(evt);
            }
        });

        input_path.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                input_pathActionPerformed(evt);
            }
        });

        output_path.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                output_pathActionPerformed(evt);
            }
        });

        get_input_path.setText("Browse");
        get_input_path.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                get_input_pathActionPerformed(evt);
            }
        });

        get_output_path.setText("Browse");
        get_output_path.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                get_output_pathActionPerformed(evt);
            }
        });

        jLabel2.setText("Input file");

        jLabel3.setText("Output");

        odbicia.setFont(new java.awt.Font("Dialog", 1, 14)); // NOI18N
        odbicia.setSelected(true);
        odbicia.setText("Odbicia");
        odbicia.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        odbicia.setIconTextGap(5);
        odbicia.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                odbiciaActionPerformed(evt);
            }
        });

        n_o_cykle.setModel(new javax.swing.SpinnerNumberModel(1, 1, 10, 1));
        n_o_cykle.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        n_o_cykle.setOpaque(false);
        n_o_cykle.setValue(1);

        jLabel1.setFont(new java.awt.Font("Dialog", 1, 14)); // NOI18N
        jLabel1.setText("Ilosc cykli:");

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGap(100, 100, 100)
                .addComponent(odbicia)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 134, Short.MAX_VALUE)
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(n_o_cykle, javax.swing.GroupLayout.PREFERRED_SIZE, 60, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(100, 100, 100))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(n_o_cykle, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel1)
                    .addComponent(odbicia))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(26, 26, 26)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(jLabel2)
                            .addComponent(jLabel3))
                        .addGap(18, 18, 18)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(input_path)
                            .addComponent(output_path, javax.swing.GroupLayout.DEFAULT_SIZE, 398, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(get_input_path, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(get_output_path, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(input_path, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(get_input_path)
                    .addComponent(jLabel2))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(output_path, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jLabel3)
                    .addComponent(get_output_path))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(0, 0, Short.MAX_VALUE))
        );

        start_run.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        start_run.setText("START");
        start_run.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                start_runActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel3Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(start_run, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(16, 16, 16))
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel3Layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(start_run, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(24, 24, 24))
        );

        load_label.setFont(new java.awt.Font("Dialog", 1, 18)); // NOI18N
        load_label.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        load_label.setHorizontalTextPosition(javax.swing.SwingConstants.CENTER);

        javax.swing.GroupLayout IMG_loadLayout = new javax.swing.GroupLayout(IMG_load);
        IMG_load.setLayout(IMG_loadLayout);
        IMG_loadLayout.setHorizontalGroup(
            IMG_loadLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(load_label, javax.swing.GroupLayout.DEFAULT_SIZE, 720, Short.MAX_VALUE)
        );
        IMG_loadLayout.setVerticalGroup(
            IMG_loadLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(load_label, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 467, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(IMG_load, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 720, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, 587, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(jPanel3, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 10, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(IMG_load, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>

    private void input_pathActionPerformed(java.awt.event.ActionEvent evt) {

    }

    private void odbiciaActionPerformed(java.awt.event.ActionEvent evt) {
    }

    private void get_input_pathActionPerformed(java.awt.event.ActionEvent evt) {
        //obsługa przycisku "Browse" przy polu input
        JFileChooser chooser = new JFileChooser();
        int returnVal = chooser.showOpenDialog(null);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            input_path.setText(chooser.getSelectedFile().getAbsolutePath());
        }
    }

    private void output_pathActionPerformed(java.awt.event.ActionEvent evt) {

    }

    private void get_output_pathActionPerformed(java.awt.event.ActionEvent evt) {
        //obsługa przycisku "Browse" przy polu output 
        JFileChooser f = new JFileChooser();
        f.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        f.showSaveDialog(null);
        System.out.println(f.getSelectedFile());

        if (f.getSelectedFile() != null) {
            output_path.setText(f.getSelectedFile().getAbsolutePath());
        } else {
            output_path.setText(System.getProperty("user.dir"));
        }

    }

    private void formWindowActivated(java.awt.event.WindowEvent evt) {
        //output_path.setText(System.getProperty("user.dir"));
    }

    private void start_runActionPerformed(java.awt.event.ActionEvent evt) {
        //czyszczenie pola do wyswietlenia trawnika
        load_label.setIcon(new ImageIcon("img\\ajax-loader.gif"));
        
        //pobranie wartosci uruchomienia programu
        String output = output_path.getText();
        String input = input_path.getText();
        int cykle = (int) n_o_cykle.getValue();
        boolean odb = odbicia.isSelected();

        //przypisanie wartosci domyslnych, jezeli uzytkownik ich nie poda
        cykle = cykle != 0 ? cykle : 1;
        input = !input.isEmpty() ? input : System.getProperty("user.dir") + "\\dane1.txt";
        output = !output.isEmpty() ? output : System.getProperty("user.dir");//domyslna wartosc to obecny katalog roboczy uzytkownika
        
        //sprawdzenie czy wybrany katoalog wyjsciowy istanieje, ejsli nie to tworzy
        File out_test = new File(output);
        if(! out_test.exists())
            out_test.mkdir();
        
        System.out.println("input: " + input);
        System.out.println("output: " + output);
        System.out.println("cykle: " + cykle);
        System.out.println("odbicia: " + odb);

        //uruchomienie programu 
        //jak zwraca wartosc 0 to wszystko zakonczylo sie pomyslnie
        //w kazdym innym przyapdku wystapily bledy
        try {
            if (Start_prog.run(cykle, odb, input, output) == 0) {
                System.out.println("COMPLETED!");
                JOptionPane.showMessageDialog(null, "PODLEWANIE TRAWNIKA ZAKOCZNYLO SIE POWODZENIEM!", "Sukces!", JOptionPane.INFORMATION_MESSAGE);
                File bmpFile = new File(output + "\\out_bmp.bmp");
                BufferedImage image = ImageIO.read(bmpFile);
                Image scalled_image = image.getScaledInstance(load_label.getWidth(), load_label.getHeight(), Image.SCALE_SMOOTH);
                load_label.setIcon(new ImageIcon(scalled_image));

            } else {
                load_label.setIcon(new ImageIcon("img\\error.png"));
                JOptionPane.showMessageDialog(null, "NIE UDALO SIE PODLAC TRAWNIKA!", "Error!", JOptionPane.ERROR_MESSAGE);
            }
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "W TRAKCIE DZIALANIA PROGRAMU WYSTAPIL BLAD!", "Error!", JOptionPane.ERROR_MESSAGE);
        }
    }


    // Variables declaration - do not modify
    private javax.swing.JPanel IMG_load;
    private javax.swing.JButton get_input_path;
    private javax.swing.JButton get_output_path;
    private javax.swing.JTextField input_path;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JSeparator jSeparator2;
    private javax.swing.JLabel load_label;
    private javax.swing.JSpinner n_o_cykle;
    private javax.swing.JCheckBox odbicia;
    private javax.swing.JTextField output_path;
    private javax.swing.JButton start_run;
    // End of variables declaration

}



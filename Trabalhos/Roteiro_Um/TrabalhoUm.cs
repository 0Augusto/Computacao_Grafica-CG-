//---------------------------------------------------------------------
// TransformacoesGeometricas - Aplicação para demonstrar transformações geométricas em um ambiente gráfico.
// Autor: Henrique Augusto Rodrigues
// Versão: 1.0
// Data: 09/08/2023
//---------------------------------------------------------------------

// Importação das bibliotecas necessárias
using System;
using System.Drawing;
using System.Windows.Forms;

namespace TransformacoesGeometricas
{
    public partial class tela : Form
    {
        // Atributos da classe
        private Bitmap areaDesenho;
        private Color corPreenche;

        // Construtor da classe
        public tela()
        {
            InitializeComponent();

            // Inicialização dos atributos
            areaDesenho = new Bitmap(imagem.Size.Width, imagem.Size.Height);
            corPreenche = Color.Black;
        }

        // Evento de clique no botão "Desenhar"
        private void desenhar_Click(object sender, EventArgs e)
        {
            // Obtenção das coordenadas x e y a partir dos campos de texto
            int x = Convert.ToInt32(txtX.Text);
            int y = Convert.ToInt32(txtY.Text);

            // Desenho de um ponto na área de desenho na coordenada (x, y) com a cor definida
            areaDesenho.SetPixel(x, y, corPreenche);

            // Atualização da imagem exibida na PictureBox
            imagem.Image = areaDesenho;
        }

        // Evento de clique no botão "Cor"
        private void btCor_Click(object sender, EventArgs e)
        {
            // Exibição do diálogo de seleção de cor
            DialogResult result = cdlg.ShowDialog();
            if (result == DialogResult.OK)
            {
                // Atualização da cor de preenchimento
                corPreenche = cdlg.Color;
            }
        }

        // Evento de clique no botão "Apagar"
        private void btApagar_Click(object sender, EventArgs e)
        {
            // Criação de uma nova área de desenho (imagem em branco)
            areaDesenho = new Bitmap(imagem.Size.Width, imagem.Size.Height);

            // Atualização da imagem exibida na PictureBox
            imagem.Image = areaDesenho;
        }

        // Evento de movimento do mouse na área de desenho
        private void imagem_MouseMove(object sender, MouseEventArgs e)
        {
            // Verificação se o botão esquerdo do mouse está pressionado
            if (e.Button == MouseButtons.Left)
            {
                // Obtenção das coordenadas x e y do mouse
                int x = e.X;
                int y = e.Y;

                // Atualização dos campos de texto com as coordenadas x e y
                txtX.Text = Convert.ToString(x);
                txtY.Text = Convert.ToString(y);

                // Desenho de um ponto na área de desenho na coordenada (x, y) com a cor definida
                areaDesenho.SetPixel(x, y, corPreenche);

                // Atualização da imagem exibida na PictureBox
                imagem.Image = areaDesenho;
            }
        }

        // Evento de clique no botão "Transformar"
        private void btTransformar_Click(object sender, EventArgs e)
        {
            // Lógica das transformações geométricas
            double angle = Convert.ToDouble(txtAngulo.Text);
            double dx = Convert.ToDouble(txtTransX.Text);
            double dy = Convert.ToDouble(txtTransY.Text);
            double sx = Convert.ToDouble(txtEscalaX.Text);
            double sy = Convert.ToDouble(txtEscalaY.Text);
            double shx = Convert.ToDouble(txtCisalhamentoX.Text);
            double shy = Convert.ToDouble(txtCisalhamentoY.Text);

            // Aplicação das transformações ao ponto original (1.0, 1.0)
            Point2D originalPoint = new Point2D(1.0, 1.0);
            Point2D rotatedPoint = rotate(originalPoint, angle);
            Point2D translatedPoint = translate(rotatedPoint, dx, dy);
            Point2D reflectedPoint = reflect(translatedPoint);
            Point2D scaledPoint = new Point2D(translatedPoint.x * sx, translatedPoint.y * sy);
            Point2D shearedPoint = new Point2D(scaledPoint.x + scaledPoint.y * shx, scaledPoint.y + scaledPoint.x * shy);

            // Plot dos gráficos usando gnuplot
            string gnuplotCmd = "set multiplot layout 1, 5\n";
            gnuplotCmd += "plot '-' with points title 'Original'\n" + originalPoint.x + " " + originalPoint.y + "\ne\n";
            gnuplotCmd += "plot '-' with points title 'Rotacionado'\n" + rotatedPoint.x + " " + rotatedPoint.y + "\ne\n";
            gnuplotCmd += "plot '-' with points title 'Transladado'\n" + translatedPoint.x + " " + translatedPoint.y + "\ne\n";
            gnuplotCmd += "plot '-' with points title 'Escalado'\n" + scaledPoint.x + " " + scaledPoint.y + "\ne\n";
            gnuplotCmd += "plot '-' with points title 'Cisalhado'\n" + shearedPoint.x + " " + shearedPoint.y + "\ne\n";

            // Execução do comando gnuplot para exibir os gráficos
            // Obs: Certifique-se de que o gnuplot esteja instalado e acessível pelo caminho do sistema
            FILE *gnuplot = popen("gnuplot -persist", "w");
            fprintf(gnuplot, gnuplotCmd);
            fclose(gnuplot);
        }
    }

    // Estrutura para representar um ponto 2D
    class Point2D
    {
        public double x, y;

        // Construtor da classe Point2D
        public Point2D(double x, double y)
        {
            this.x = x;
            this.y = y;
        }
    }
}


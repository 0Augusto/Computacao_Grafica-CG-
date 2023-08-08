#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QInputDialog>
#include <math.h>

// Funções de transformação (como as do seu código)
// ...

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("Transformações 2D");
    
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    
    QPushButton applyButton("Aplicar Transformações");
    
    // Conectar o clique do botão com a função de transformações
    QObject::connect(&applyButton, &QPushButton::clicked, [&]() {
        bool ok;
        QPointF point1 = QInputDialog::getPointF(&window, "Selecionar Ponto 1", "Coordenadas do Ponto 1:", QPointF(), QPointF(-1000, -1000), QPointF(1000, 1000), 2, &ok);
        if (!ok) return;
        
        QPointF point2 = QInputDialog::getPointF(&window, "Selecionar Ponto 2", "Coordenadas do Ponto 2:", QPointF(), QPointF(-1000, -1000), QPointF(1000, 1000), 2, &ok);
        if (!ok) return;
        
        // Aplicar transformações e plotar os gráficos
        // ...
        
        // Atualizar a cena com os pontos e gráficos resultantes
        scene.clear();
        // Desenhar os pontos e gráficos na cena
        // ...
    });
    
    scene.setSceneRect(-1000, -1000, 2000, 2000);
    
    // Adicionar os elementos à janela
    QVBoxLayout layout(&window);
    layout.addWidget(&view);
    layout.addWidget(&applyButton);
    
    window.setLayout(&layout);
    window.show();
    
    return app.exec();
}


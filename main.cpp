#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector>
#include <QQueue>
#include <QTimer>
#include <QTime>
#include <queue>
#include <QMessageBox>
#include <QRandomGenerator>
#include <cstdlib>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QTextEdit>
#include <QInputDialog>




class GraphWidget : public QGraphicsView
{
private:

    QVector<QVector<int>> adjacencyMatrix;
    QVector<QVector<int>> WMatrix;

    int n;
public:

    GraphWidget(int vertices, QWidget *parent = nullptr) : QGraphicsView(parent), n(vertices)
    {
        QGraphicsScene *scene = new QGraphicsScene(this);
        setScene(scene);



        if(n == 1)
        {
        // Пример матрицы смежности (0 - нет ребра, 1 - есть ребро)
        /*int Matrix[6][6] = {
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 1, 0},
                            {0, 0, 0, 1, 0, 1},
                            {0, 0, 1, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0},
                            {0, 0, 1, 1, 0, 0},
                            };


*/


        int Matrix[9][9] = {
            {0, 1, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 0, 0, 1, 0, 1},
            {0, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 1, 0}
        };


        // Заполнение adjacencyMatrix из Matrix
        for (int i = 0; i < 9; ++i) {
            QVector<int> rowVector;
            for (int j = 0; j < 9; ++j) {
                rowVector.append(Matrix[i][j]);
            }
            adjacencyMatrix.append(rowVector);
        }


        int n = 9;
        int m = n;
        WMatrix = QVector<QVector<int>>(m, QVector<int>(m, 0));
        QRandomGenerator generator;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {   // Проверяем, что между вершинами i и j существует путь
                    int weight = generator.bounded(10) + 1;  // Генерируем случайный вес от 1 до 10
                    WMatrix[i][j] = weight;
                    WMatrix[j][i] = weight;  // Матрица весов симметрична, поэтому устанавливаем вес и для обратного пути
                }
            }
        }

        //создаем невзвешенный граф неоориентированный через матрицк смежности
        DEMOcreateGraphFromAdjacencyMatrix(scene, adjacencyMatrix);
        }
        else
        {







       //int n = 25;
       //QVector<QVector<int>> adjacencyMatrix(n, QVector<int>(n, 0));
        adjacencyMatrix = QVector<QVector<int>>(n, QVector<int>(n, 0));

        // Заполнение матрицы смежности(раньше до числа p была 5)
        bool ok;
        int p = QInputDialog::getInt(nullptr, "Введите число", "P - Общее количество возможностей выбора. Введите число p:", 0, 0, INT_MAX, 1, &ok);

        if (ok)
        {
        QRandomGenerator generator;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j)
            {
                if (generator.bounded(p) == 0) {
                    adjacencyMatrix[i][j] = 1;
                    adjacencyMatrix[j][i] = 1;
                }
            }
        }
        }
        //printAdjacencyMatrix(adjacencyMatrix);



        int m = n;
        WMatrix = QVector<QVector<int>>(m, QVector<int>(m, 0));
        QRandomGenerator generator;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {   // Проверяем, что между вершинами i и j существует путь
                    int weight = generator.bounded(10) + 1;  // Генерируем случайный вес от 1 до 10
                    WMatrix[i][j] = weight;
                    WMatrix[j][i] = weight;  // Матрица весов симметрична, поэтому устанавливаем вес и для обратного пути
                }
            }
        }





        //создаем взвешенный граф неориентированный через матрицу весов
        //createWeightedGraphFromAdjacencyMatrix(scene, WMatrix);

        //создаем невзвешенный граф неоориентированный через матрицк смежности
        DEMOcreateGraphFromAdjacencyMatrix(scene, adjacencyMatrix);

        int graph[5][5] = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0}
        };

        //primMST(graph);



        ///ранее было уже не актуально
        //depthFirstSearch(scene, adjacencyMatrix);
        //removeVertexAndUpdateGraph(scene, adjacencyMatrix, 0);
        }

    }

    // Вывод матрицы смежности в консоль
    void printAdjacencyMatrix(const QVector<QVector<int>> &adjacencyMatrix)
    {
        for (int i = 0; i < adjacencyMatrix.size(); ++i) {
            for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
                qDebug() << adjacencyMatrix[i][j] << " ";
            }
            qDebug() << Qt::endl;
        }
    }


    //структура ребра для алгоритма Крускала(начальная вершина, конечная вершина, вес ребра)
    struct Edge {
        int src, dest, weight;
    };


    int findSubset(int parent[], int i) {
        if (parent[i] != i) {
            parent[i] = findSubset(parent, parent[i]); //находим корень подмножества в которому принадлежит i
        }
        return parent[i];
    }

    //Объединение множеств
    void unionSubsets(int parent[], int rank[], int x, int y)
    {
        //находим корни для элементов
        int xroot = findSubset(parent, x);
        int yroot = findSubset(parent, y);
        //если высота дерева меньше
        if (rank[xroot] < rank[yroot])
        {
            parent[xroot] = yroot; //корень xroot становится дочерним элементом дерева yroot
        } else if (rank[xroot] > rank[yroot])
        {
            parent[yroot] = xroot;
        } else //если же высоты одинаковые, то один становится дочерним, а высота второго увеличивается на 1 (нет разницы какие именно деревья)
        {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }


    //Алгоритм Крускала (O(ElogE))
    void createWeightedGraphFromAdjacencyMatrix(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix,const QVector<QVector<int>> &WMatrix )
    {

        scene->clear();

        QVector<QGraphicsEllipseItem*> nodes;

        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    // Рисуем ребро с весом
                    QGraphicsLineItem *edge = scene->addLine(
                        nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                        nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                        );
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(WMatrix[i][j]));
                    weightText->setPos((nodes[i]->pos().x() + nodes[j]->pos().x()) / 2, (nodes[i]->pos().y() + nodes[j]->pos().y()) / 2);
                }
            }
        }

        int V = adjacencyMatrix.size();
        QVector<Edge> edges;
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    Edge edge;
                    edge.src = i;
                    edge.dest = j;
                    edge.weight = WMatrix[i][j];
                    edges.push_back(edge);
                }
            }
        }

        //соритровка ребер по весу
        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        //вектор для хранения ребер минимального остовного дерева
        QVector<Edge> minimumSpanningTree;
        int parent[V]; //хранит представителя каждого узла
        int rank[V]; //используется для оптимизации объединения множеств
        for (int v = 0; v < V; ++v)
        {
            parent[v] = v;
            rank[v] = 0;
        }

        //проверка всех ребер, не принадлежат ли концы каждого ребра к одному и тому же поддереву
        //если концы находятся в разных поддеревьяъ, то ребра добавляются к минимальному остовному дереву и потом объединяются
        for (const Edge &edge : edges)
        {
            int x = findSubset(parent, edge.src);
            int y = findSubset(parent, edge.dest);
            if (x != y)
            {
                minimumSpanningTree.append(edge);
                unionSubsets(parent, rank, x, y);
            }
        }

        //перекрашиваем ветки в зеленый - ветки минимального остовного дерева
        for (const Edge &edge : minimumSpanningTree)
        {
            QGraphicsLineItem *treeEdge = scene->addLine(
                nodes[edge.src]->pos().x() + 25, nodes[edge.src]->pos().y() + 25,
                nodes[edge.dest]->pos().x() + 25, nodes[edge.dest]->pos().y() + 25
                );
            treeEdge->setPen(QPen(Qt::green));
            QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(edge.weight));
            weightText->setPos((nodes[edge.src]->pos().x() + nodes[edge.dest]->pos().x()) / 2, (nodes[edge.src]->pos().y() + nodes[edge.dest]->pos().y()) / 2);
        }

        // Output Kruskal's Minimum Spanning Tree
        qDebug() << "Kruskal's Minimum Spanning Tree:";
        for (const Edge &edge : minimumSpanningTree) {
            qDebug() << edge.src << " - " << edge.dest << " : " << edge.weight;
        }

    }

    // Дополнение кода createWeightedGraphFromAdjacencyMatrixPrim


        //Алгоритм Прима для нахождения минимального остовного дерева (O(V^2))
    void createWeightedGraphFromAdjacencyMatrixPrim(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix, const QVector<QVector<int>> &WMatrix) {
        int numVertices = adjacencyMatrix.size();

        std::vector<int> parent(numVertices); //Массив для хранения родительских вершин
        std::vector<int> key(numVertices, INT_MAX); //Массив для хранения ключей (весов) вершин
        std::vector<bool> mstSet(numVertices, false); //Массив для отслеживания вершин, уже включенных в остовное дерево

        key[0] = 0; //Начинаем с вершины 0
        parent[0] = -1; //Начальной вершине не назначаем родителя

        //каждая итерация цикла добавляет одно ребро к минимальному остновному дереву
        for (int count = 0; count < numVertices - 1; ++count)
        {
            int u = -1;
            //цикл проходящий по всем вершинам с поиском v удовл специальным условиям
            for (int v = 0; v < numVertices; ++v)
            {
                //если вершина не включена в остовное дерево и вершина не является -1(т.е. ее еще не выбирали) либо ключ ее меньше u
                if (!mstSet[v] && (u == -1 || key[v] < key[u]))
                {
                    u = v; //при выполнении условий вершина v становится u
                }
            }

            mstSet[u] = true; //пометили как включенную в остовное дерево

            //обновление ключей для смежных с вершиной u и имеют меньший вес, чем ключ этой вершины
            for (int v = 0; v < numVertices; ++v)
            {
                if (adjacencyMatrix[u][v] && !mstSet[v] && WMatrix[u][v] < key[v])
                {
                    //обновляем родительскую вершину и ключ для вершины V
                    parent[v] = u;
                    key[v] = WMatrix[u][v];
                }
            }
        }

        qDebug() << "Ребро \tВес";
        for (int i = 1; i < numVertices; ++i)
        {
            qDebug() << parent[i] << " - " << i << "\t" << WMatrix[i][parent[i]];
        }
    }

    void TimeComparisonKruskalPrim(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix,const QVector<QVector<int>> &WMatrix )
    {
        QElapsedTimer timer;
        timer.start();



        scene->clear();

        QVector<QGraphicsEllipseItem*> nodes;

        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    // Рисуем ребро с весом
                    QGraphicsLineItem *edge = scene->addLine(
                        nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                        nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                        );
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(WMatrix[i][j]));
                    weightText->setPos((nodes[i]->pos().x() + nodes[j]->pos().x()) / 2, (nodes[i]->pos().y() + nodes[j]->pos().y()) / 2);
                }
            }
        }

        int V = adjacencyMatrix.size();
        QVector<Edge> edges;
        for (int i = 0; i < V; ++i) {
            for (int j = i + 1; j < V; ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    Edge edge;
                    edge.src = i;
                    edge.dest = j;
                    edge.weight = WMatrix[i][j];
                    edges.push_back(edge);
                }
            }
        }
        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        QVector<Edge> minimumSpanningTree;
        int parent[V];
        int rank[V];
        for (int v = 0; v < V; ++v) {
            parent[v] = v;
            rank[v] = 0;
        }

        for (const Edge &edge : edges) {
            int x = findSubset(parent, edge.src);
            int y = findSubset(parent, edge.dest);
            if (x != y) {
                minimumSpanningTree.append(edge);
                unionSubsets(parent, rank, x, y);
            }
        }

        // Highlight the minimum spanning tree edges in yellow
        for (const Edge &edge : minimumSpanningTree) {
            QGraphicsLineItem *treeEdge = scene->addLine(
                nodes[edge.src]->pos().x() + 25, nodes[edge.src]->pos().y() + 25,
                nodes[edge.dest]->pos().x() + 25, nodes[edge.dest]->pos().y() + 25
                );
            treeEdge->setPen(QPen(Qt::green));  // Set the edge color to green
            QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(edge.weight));
            weightText->setPos((nodes[edge.src]->pos().x() + nodes[edge.dest]->pos().x()) / 2, (nodes[edge.src]->pos().y() + nodes[edge.dest]->pos().y()) / 2);
        }

        // Output Kruskal's Minimum Spanning Tree
        qDebug() << "Kruskal's Minimum Spanning Tree:";
        for (const Edge &edge : minimumSpanningTree) {
            qDebug() << edge.src << " - " << edge.dest << " : " << edge.weight;
        }

        qint64 elapsed = timer.elapsed();
        qDebug() << "Время выполнения: " << elapsed*1000000 << "нс";
        //сложность выполнения алгоритма О(e*logv)

        QElapsedTimer timer2;
        timer2.start();

        //теперь алгоритм прима
        int numVertices = adjacencyMatrix.size();

        std::vector<int> parent2(numVertices); // Массив для хранения родительских вершин
        std::vector<int> key(numVertices, INT_MAX); // Массив для хранения ключей (весов) вершин
        std::vector<bool> mstSet(numVertices, false); // Массив для отслеживания вершин, уже включенных в остовное дерево

        key[0] = 0; // Начинаем с вершины 0
        parent[0] = -1; // Начальной вершине не назначаем родителя

        for (int count = 0; count < numVertices - 1; ++count) {
            int u = -1;
            for (int v = 0; v < numVertices; ++v) {
                if (!mstSet[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            mstSet[u] = true;

            for (int v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] && !mstSet[v] && WMatrix[u][v] < key[v]) {
                    parent2[v] = u;
                    key[v] = WMatrix[u][v];
                }
            }
        }

        qDebug() << "Ребро \tВес";
        for (int i = 1; i < numVertices; ++i) {
            qDebug() << parent2[i] << " - " << i << "\t" << WMatrix[i][parent2[i]];
        }

        qint64 elapsed2 = timer2.elapsed();
        qDebug() << "Время выполнения: " << elapsed2 << "мс";
        //Сложность Алг Прима О(V^2)
    QGraphicsTextItem *textItem = scene->addText("Время выполнения алгоритмов:");
        textItem->setDefaultTextColor(Qt::red);
        textItem->setPos(10, 10);


        QGraphicsTextItem *result = scene->addText("(мс) O(E*lgV) Алгоритм Краскала: " + QString::number(elapsed));
        result->setPos(10, 30);
        QGraphicsTextItem *result2 = scene->addText("(мс) O(V^2) Алгоритм Прима: " + QString::number(elapsed2));
        result2->setPos(10, 50);

    }


    //Алгоритм Беллмана-Форда(O(V*E))
    void createWeightedGraphFromMatrix(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix, const QVector<QVector<int>> &WMatrix) {
        const int INF = std::numeric_limits<int>::max(); // Используем максимальное значение int в качестве бесконечности

        scene->clear();

        QVector<QGraphicsEllipseItem*> nodes;

        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    // Рисуем ребро с весом
                    QGraphicsLineItem *edge = scene->addLine(
                        nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                        nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                        );
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(WMatrix[i][j]));
                    weightText->setPos((nodes[i]->pos().x() + nodes[j]->pos().x()) / 2, (nodes[i]->pos().y() + nodes[j]->pos().y()) / 2);
                }
            }
        }

        // Алгоритм Беллмана-Форда для поиска минимального пути от вершины 0 до всех остальных вершин
        QVector<int> distances(adjacencyMatrix.size(), INF);
        distances[0] = 0; // пометили вершину, от которой ищем минимальные пути

        //итерация по всем вершинам графа, кроме последней
        for (int v = 0; v < adjacencyMatrix.size() - 1; ++v)
        {
            for (int i = 0; i < adjacencyMatrix.size(); ++i) //перебор всех вершин графа
            {
                for (int j = 0; j < adjacencyMatrix[i].size(); ++j) //перебор всех смежных вершин графа
                {
                    if (adjacencyMatrix[i][j] != 0)//если есть ребро между вершинами
                    {
                    //проверка на улучшение до тех пока, пока не получим оптимальные расстояния от вершины 0 до другой вершины
                        if (distances[i] != INF && distances[i] + WMatrix[i][j] < distances[j])
                        {
                            distances[j] = distances[i] + WMatrix[i][j];
                        }
                    }
                }
            }
        }

        // Выводим результаты минимального пути
        for (int i = 0; i < distances.size(); ++i) {
            qDebug() << "Минимальный путь от вершины 0 до вершины " << i << " равен " << distances[i];
        }

QGraphicsTextItem *textItem = scene->addText("Минимальные пути от вершины 0:");
    textItem->setPos(10, 10);
    for (int i = 0; i < distances.size(); ++i) {
        QGraphicsTextItem *result = scene->addText("До вершины " + QString::number(i) + " : " + QString::number(distances[i]));
        result->setPos(10, 30 + i * 20);
    }
    }







    void DEMOcreateGraphFromAdjacencyMatrix(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix)
    {

        scene->clear();

        QMessageBox::information(nullptr, "Лабораторная работа 2", "Костин Максим - ИВБ - 215");


        QVector<QGraphicsEllipseItem*> nodes;
        QVector<QGraphicsLineItem*> edges;

        //QGraphicsSimpleTextItem *startText = scene->addSimpleText("start");
        //startText->setPos(scene->width()/2, scene->height()/2);



        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < 30; ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);
        }

        // Создаем ребра графа между всеми вершинами
        for (int i = 0; i < nodes.size(); ++i)
        {
            for (int j = i + 1; j < nodes.size(); ++j)
            {
                QGraphicsLineItem *edge = scene->addLine(
                    nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                    nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                    );
                edges.append(edge);  // Добавляем ребро в вектор для последующей анимации
            }
        }

        // Создаем и запускаем таймер для анимации изменения цвета
        QTimer *timer = new QTimer();
        connect(timer, &QTimer::timeout, [=]() {
            for (int i = 0; i < nodes.size(); ++i) {
                QColor newColor = QColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
                nodes[i]->setBrush(QBrush(newColor));
            }
            for (int i = 0; i < edges.size(); ++i) {
                QColor newColor = QColor(std::rand() % 256, std::rand() % 256, std::rand() % 256);
                edges[i]->setPen(QPen(newColor, 2));
            }
        });
        timer->start(1000);  // Запускаем таймер, чтобы изменения происходили каждую секунду





        QGraphicsTextItem *textItem = scene->addText("Hello");  // Создание текста "Hello" и добавление его на сцену
        textItem->setDefaultTextColor(Qt::black);  // Установка цвета текста
        textItem->setFont(QFont("Arial", 70));  // Начальный размер шрифта и тип шрифта
        textItem->setPos(scene->width() / 2 - textItem->boundingRect().width() / 2, scene->height() / 2 - textItem->boundingRect().height() / 2);  // Позиционирование текста по центру сцены

        QPropertyAnimation *posAnimation = new QPropertyAnimation(textItem, "pos");
        posAnimation->setDuration(4000);  // 9 секунд для анимации
        posAnimation->setStartValue(QPointF(scene->width() / 2, scene->height() / 2));  // Начальная позиция - центр сцены
        posAnimation->setKeyValueAt(0, QPointF(scene->width() / 2 + 100, scene->height() / 2));  // Позиция текста на 0% времени
        posAnimation->setKeyValueAt(0.25, QPointF(scene->width() / 2, scene->height() / 2 + 100));  // Позиция текста на 25% времени
        posAnimation->setKeyValueAt(0.5, QPointF(scene->width() / 2 - 100, scene->height() / 2));  // Позиция текста на 50% времени
        posAnimation->setKeyValueAt(0.75, QPointF(scene->width() / 2, scene->height() / 2 - 100));  // Позиция текста на 75% времени
        posAnimation->setEndValue(QPointF(scene->width() / 2 + 100, scene->height() / 2));  // Конечная позиция
        posAnimation->setEasingCurve(QEasingCurve::Linear);  // Использование линейной кривой для равномерного движения по кругу
        posAnimation->setLoopCount(-1);  // Бесконечное повторение анимации

        posAnimation->start();

        QPushButton *stopButton = new QPushButton("Stop Animations");
        stopButton->setGeometry(50, 100, 100, 50);  // Установка положения и размеров кнопки
        scene->addWidget(stopButton);  // Добавление кнопки на сцену

        // Создание анимации для кнопки
        QPropertyAnimation *buttonPosAnimation = new QPropertyAnimation(stopButton, "pos");
        buttonPosAnimation->setDuration(9000);  // 9 секунд для анимации
        buttonPosAnimation->setStartValue(QPoint(10, 50));  // Начальное положение кнопки
        buttonPosAnimation->setEndValue(QPoint(10, 750));  // Конечное положение кнопки
        buttonPosAnimation->setEasingCurve(QEasingCurve::InOutQuad);  // Использование параболической кривой для движения
        //buttonPosAnimation->setLoopCount(-1);  // Бесконечное повторение анимации

        buttonPosAnimation->start();

        // Подключение сигнала clicked к слоту остановки таймеров и анимаций
        connect(stopButton, &QPushButton::clicked, [=]() {
            // Остановка всех таймеров
            timer->stop();

            // Остановка всех анимаций
            posAnimation->stop();

            // Остановка любых других анимаций и таймеров на сцене
            // (если такие имеются, их нужно также указать для остановки)
        });


    }


    void DEMOcreateGraphFromAdjacencyMatrix0(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix)
    {
        scene->clear();
        QVector<QGraphicsEllipseItem*> nodes;

        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (int j = i + 1; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] == 1)
                {
                    QGraphicsLineItem *edge = scene->addLine(
                        nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                        nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                        );
                }
            }
        }
    }


    //Метод для графической реализации DFS-обхода графа (O(V+E) - сумма числа вершин и ребер)
    void createGraphFromAdjacencyMatrix(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix)
    {
        scene->clear();//очистка сцены от предыдущих объектов

        //QHash реализован с помощьб квадратичного пробирования(открытая адресация, основан на массива пар: ключ-значение)
        QHash<int, QGraphicsEllipseItem*> nodeMap; // Используем хеш-таблицу для хранения номеров вершин и соответствующих эллипсов

        // Создаем узлы графа в случайных позициях и добавляем номера вершин
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            int x = rand() % 800 + 50; //Генерируем случайные координаты для x, y в рамках 800х800
            int y = rand() % 800 + 50;
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodeMap.insert(i, node); // Добавляем эллипс в хеш-таблицу под определенным номером

            //СОздаем номер вершины
            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i));
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }



        //Создаем ребра графа на основе матрицы смежности
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (int j = i + 1; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] == 1)
                {
                    //метод addline принимает 4 параметра(x1,y1,x2,y2 и строит между ними линию)
                    QGraphicsLineItem *edge = scene->addLine(
                        nodeMap.value(i)->pos().x() + 25, nodeMap.value(i)->pos().y() + 25,
                        nodeMap.value(j)->pos().x() + 25, nodeMap.value(j)->pos().y() + 25
                        );
                }
            }
        }



        // Вызываем обход в глубину (DFS) с раскрашиванием вершин в зеленый цвет и выводом номеров посещенных вершин в консоль

        QVector<bool> visited(nodeMap.size(), false); // Создаем вектор посещенных вершин
        int counter = 0; // Счетчик для задержки цвета


        int userMultiplier;
        bool ok;
        do {
            QString text = QInputDialog::getText(0, "Управление скоростью таймера", "Введите число для умножения счетчика таймера:", QLineEdit::Normal, QString(), &ok);
            if (ok && !text.isEmpty()) {
                userMultiplier = text.toInt(&ok);
            } else {
                return; // Пользователь отменил ввод или не ввел число, прерываем выполнение метода
            }
        } while (!ok || userMultiplier <= 0); // Повторяем запрос, пока не получим корректное значение от пользователя



        for (int i = 0; i < nodeMap.size(); ++i)
        {
            if (!visited[i])
            {
                //Обход по ветке вершины, если она еще не полностью пройдена
                dfsUtil(scene, nodeMap, visited, adjacencyMatrix, i, counter, userMultiplier); // Вызываем dfsUtil для каждой непосещенной вершины
            }
        }


    }


    void dfsUtil(QGraphicsScene *scene, QHash<int, QGraphicsEllipseItem*> &nodeMap, QVector<bool> &visited, const QVector<QVector<int>> &adjacencyMatrix, int nodeIndex, int &counter, int userMultiplier)
    {
        visited[nodeIndex] = true; //отмечаем, что посетили вершину
        qDebug() << "Посещена вершина: " << nodeIndex; // Выводим номер посещенной вершины в консоль



        QGraphicsEllipseItem *node = nodeMap.value(nodeIndex); // Получаем эллипс из хеш-таблицы
        if (node != nullptr)
        {

            QTimer::singleShot(counter * userMultiplier, [node]() {
                node->setBrush(Qt::green); // Устанавливаем цвет вершины на зеленый
            });
            counter++;
        }

        for (int i = 0; i < adjacencyMatrix[nodeIndex].size(); ++i)
        {
            if (adjacencyMatrix[nodeIndex][i] == 1 && !visited[i]) // Проверяем, что вершина не посещена и связана с текущей
            {
                /// Добавляем путь между текущей вершиной и следующей вершиной
                QGraphicsLineItem *edge = scene->addLine(
                    nodeMap.value(nodeIndex)->pos().x() + 25, nodeMap.value(nodeIndex)->pos().y() + 25,
                    nodeMap.value(i)->pos().x() + 25, nodeMap.value(i)->pos().y() + 25
                    );
                edge->setPen(QPen(Qt::blue, 2, Qt::SolidLine)); // Устанавливаем цвет и толщину линии для ребра



                dfsUtil(scene, nodeMap, visited, adjacencyMatrix, i, counter, userMultiplier); // Рекурсивно вызываем dfsUtil для связанных вершин
            }
        }


    }



    void createBinaryTreeWithBFS(QGraphicsScene *scene, int numNodes)
    {
        scene->clear();
        QHash<int, QGraphicsEllipseItem*> nodeMap;

        QVector<int> nodeValues;
        for (int i = 0; i < numNodes; ++i) {
            nodeValues.append(rand() % 100); // Генерируем случайные значения для узлов дерева
        }

        int numLevels = log2(nodeValues.size() + 1); // Вычисляем количество уровней в двоичном дереве

        int xOffset = 800 / (pow(2, numLevels) - 1); // Определяем горизонтальное смещение между узлами на одном уровне
        int yOffset = 80; // Определяем вертикальное смещение между уровнями

        int currentLevel = 0;
        int nodesAtCurrentLevel = 1;
        int currentOffset = xOffset * pow(2, numLevels - currentLevel - 1);

        for (int i = 0; i < nodeValues.size(); ++i)
        {
            int x = currentOffset + xOffset * i - 25 - (xOffset * pow(2, numLevels - currentLevel - 1));
            int y = yOffset * currentLevel + 50;

            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodeMap.insert(i, node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(nodeValues[i]));
            text->setPos(x + 20, y + 60);

            if (i + 1 == nodesAtCurrentLevel)
            {
                currentLevel++;
                nodesAtCurrentLevel += pow(2, currentLevel);
                currentOffset = xOffset * pow(2, numLevels - currentLevel - 1);
            }
        }

        int parentNodeIndex = 0;

        for (int i = 1; i < nodeValues.size(); ++i)
        {
            if (i % 2 == 1) // Если индекс нечетный, это левый потомок
            {
                QGraphicsLineItem *edge = scene->addLine(
                    nodeMap.value(parentNodeIndex)->pos().x() + 25, nodeMap.value(parentNodeIndex)->pos().y() + 25,
                    nodeMap.value(i)->pos().x() + 25, nodeMap.value(i)->pos().y() + 25
                    );
            }
            else // Иначе это правый потомок
            {
                QGraphicsLineItem *edge = scene->addLine(
                    nodeMap.value(parentNodeIndex)->pos().x() + 25, nodeMap.value(parentNodeIndex)->pos().y() + 25,
                    nodeMap.value(i)->pos().x() + 25, nodeMap.value(i)->pos().y() + 25
                    );
                parentNodeIndex++;
            }
        }

        // Обход в ширину (BFS) с подсветкой вершин в красный цвет
        QVector<bool> visited(nodeMap.size(), false);
        QQueue<int> queue;
        int counter = 0;

        queue.enqueue(0); // Начинаем с корневой вершины

        int userMultiplier;
        bool ok;
        do {
            QString text = QInputDialog::getText(0, "Управление скоростью таймера", "Введите число для умножения счетчика таймера:", QLineEdit::Normal, QString(), &ok);
            if (ok && !text.isEmpty()) {
                userMultiplier = text.toInt(&ok);
            } else {
                return; // Пользователь отменил ввод или не ввел число, прерываем выполнение метода
            }
        } while (!ok || userMultiplier <= 0); // Повторяем запрос, пока не получим корректное значение от пользователя

        while (!queue.isEmpty())
        {
            int current = queue.dequeue();
            visited[current] = true;
            QGraphicsEllipseItem *node = nodeMap.value(current);

            if (node != nullptr)
            {
                QTimer::singleShot(counter * userMultiplier, [node]() {
                    node->setBrush(Qt::red);
                });
                counter++;
            }

            int leftChild = 2 * current + 1;
            int rightChild = 2 * current + 2;

            if (leftChild < nodeMap.size() && !visited[leftChild])
            {
                queue.enqueue(leftChild);
            }
            if (rightChild < nodeMap.size() && !visited[rightChild])
            {
                queue.enqueue(rightChild);
            }
        }
    }


    //Метод для графической реализации BFS-обхода графа (O(V+E))
    void createGraphFromAdjacencyMatrixBFS(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix)
    {
        scene->clear();
        QHash<int, QGraphicsEllipseItem*> nodeMap; // Используем хеш-таблицу для хранения номеров вершин и соответствующих эллипсов

        // Создаем узлы графа в случайных позициях и добавляем номера вершин
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodeMap.insert(i, node); // Добавляем эллипс в хеш-таблицу

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (int j = i + 1; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] == 1)
                {
                    QGraphicsLineItem *edge = scene->addLine(
                        nodeMap.value(i)->pos().x() + 25, nodeMap.value(i)->pos().y() + 25,
                        nodeMap.value(j)->pos().x() + 25, nodeMap.value(j)->pos().y() + 25
                        );
                }
            }
        }

        // Вызываем обход в ширину (BFS) с раскрашиванием вершин в красный цвет
        QVector<bool> visited(nodeMap.size(), false); // Создаем вектор посещенных вершин
        QQueue<int> queue; // Создаем очередь для BFS
        int counter = 0; // Счетчик для задержки цвета
        int userMultiplier;
        bool ok;
        do {
            QString text = QInputDialog::getText(0, "Управление скоростью таймера", "Введите число для умножения счетчика таймера:", QLineEdit::Normal, QString(), &ok);
            if (ok && !text.isEmpty()) {
                userMultiplier = text.toInt(&ok);
            } else {
                return; // Пользователь отменил ввод или не ввел число, прерываем выполнение метода
            }
        } while (!ok || userMultiplier <= 0); // Повторяем запрос, пока не получим корректное значение от пользователя


        for (int i = 0; i < nodeMap.size(); ++i) //проходим по всем вершинам
        {
            if (!visited[i])
            {
                queue.enqueue(i); //будем помещать все вершины в очередь (непосещенные вершины)
                while (!queue.isEmpty())
                {
                    int current = queue.dequeue(); //текущая вершина = первая из очереди (FIFO)
                    visited[current] = true;
                    QGraphicsEllipseItem *node = nodeMap.value(current); // Получаем эллипс из хеш-таблицы соответствующий текущей вершине
                    if (node != nullptr)
                    {
                        QTimer::singleShot(counter * userMultiplier, [node]() {
                            node->setBrush(Qt::red); // Устанавливаем цвет вершины на красный
                        });
                        counter++;
                    }

                    //перебираем все вершины связанные с текущей(смежные)

                    for (int j = 0; j < adjacencyMatrix[current].size(); ++j)
                    {
                        if (adjacencyMatrix[current][j] == 1 && !visited[j]) // Проверяем, что вершина не посещена и связана с текущей
                        {
                            queue.enqueue(j); //добавляем в очередь
                        }
                    }
                }
            }
        }
    }

    //обычный метод для очистки сцены
    void clearscene(QGraphicsScene *scene)
    {
         scene->clear();
    }







    void breadthFirstSearch(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix)
    {
        QList<QGraphicsItem*> items = scene->items();
        QVector<QGraphicsEllipseItem*> nodes;
        for (auto item : items)
        {
            QGraphicsEllipseItem *ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if (ellipseItem)
            {
                nodes.append(ellipseItem);
            }
        }

        QVector<bool> visited(nodes.size(), false);
        QQueue<int> queue;

        for (int i = 0; i < nodes.size(); ++i)
        {
            if (!visited[i])
            {
                queue.enqueue(i);
                visited[i] = true;

                while (!queue.isEmpty())
                {
                    int nodeIndex = queue.dequeue();
                    QGraphicsEllipseItem *node = nodes[nodeIndex];
                    if (node != nullptr)
                    {
                        QTimer::singleShot(nodeIndex * 1000, [node]() {
                            node->setBrush(Qt::red); // Устанавливаем цвет вершины на красный через 2 секунды
                        });

                    }

                    for (int j = 0; j < nodes.size(); ++j)
                    {
                        if (!visited[j] && adjacencyMatrix[nodeIndex][j] == 1)
                        {
                            queue.enqueue(j);
                            visited[j] = true;
                        }
                    }
                }
            }
        }
    }






    //Алгоритм построения DFS-леса: сложность - O((V+E)* k) - количество элементов в сцене
    void depthFirstForest(QGraphicsScene *scene, const QVector<QVector<int>> &adjacencyMatrix)
    {
        QList<QGraphicsItem*> items = scene->items();
        QVector<QGraphicsEllipseItem*> nodes;
        for (auto item : items) {
            QGraphicsEllipseItem *ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if (ellipseItem) {
                nodes.append(ellipseItem);
            }
        }

        QVector<bool> visited(nodes.size(), false);
        int treeCount = 0;//число полученных деревьев

        for (int i = 0; i < nodes.size(); ++i)
        {
            if (!visited[i])
            {
                //если вершина не была посещена, то создается новая графическая сцена
                QGraphicsScene *treeScene = new QGraphicsScene(this);
                treeCount++;

                int treeNodes = dfsUtil2(treeScene, nodes, visited, adjacencyMatrix, i); //вызваем DFS-обход для полученной вершины
                int treeWidth = 200; // Установите ширину сцены для отображения дерева
                int treeHeight = 400; // Установите высоту сцены для отображения дерева
                int treeX = (treeCount - 1) * treeWidth; // Расположение сцены дерева по оси X
                int treeY = scene->height()/2; // Расположение сцены дерева по оси Y
                QGraphicsView *treeView = new QGraphicsView(this);
                treeView->setScene(treeScene);
                treeView->setGeometry(treeX, treeY, treeWidth, treeHeight);
                treeView->show();

                // Создаем таймер для закрытия представления через 10 секунд
                QTimer::singleShot(5000, treeView, [treeView, treeScene](){
                    delete treeScene;
                    delete treeView;
                });
            }
        }
    }

    int dfsUtil2(QGraphicsScene *scene, QVector<QGraphicsEllipseItem*> &nodes, QVector<bool> &visited, const QVector<QVector<int>> &adjacencyMatrix, int nodeIndex)
    {
        visited[nodeIndex] = true;
        int treeX = 50; // Инициализируем начальное значение для X-координаты сцены дерева
        int treeY = scene->height() + 50;

        QGraphicsEllipseItem *node = nodes[nodeIndex];
        if (node != nullptr)
        {
            // Добавьте узел в сцену дерева
            QGraphicsEllipseItem *treeNode = scene->addEllipse(0, 0, 50, 50);
            treeNode->setPos(treeX, treeY);
            // Добавьте текстовый элемент с номером вершины в сцену дерева
            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(nodeIndex));
            text->setPos(treeX + 20, treeY + 20);
        }

        int treeNodesCount = 1; // Количество узлов в текущем дереве

        for (int i = 0; i < visited.size(); ++i)
        {
            if (!visited[i] && adjacencyMatrix[nodeIndex][i] == 1)
            {
                // Вызовите dfsUtil рекурсивно для каждой непосещенной смежной вершины
                treeNodesCount += dfsUtil2(scene, nodes, visited, adjacencyMatrix, i);
            }
        }

        return treeNodesCount;
    }



    void createGraph(QGraphicsScene *scene, int numNodes, int numEdges)
    {

    }



    void removeVertexAndUpdateGraph(QGraphicsScene *scene, QVector<QVector<int>> &adjacencyMatrix, int vertexToRemove)
    {

        if (vertexToRemove < 0 || vertexToRemove >= adjacencyMatrix.size()) {
            qDebug() << "Invalid vertex index to remove";
            return;
        }

        // Удаляем вершину и связанные с ней ребра из сцены
        QList<QGraphicsItem *> itemsToRemove;
        for (QGraphicsItem *item : scene->items()) {
            if (item->type() == QGraphicsEllipseItem::Type || item->type() == QGraphicsLineItem::Type) {
                int nodeIndex = item->data(0).toInt();  // Получаем индекс вершины из пользовательских данных
                if (nodeIndex == vertexToRemove) {
                    itemsToRemove.append(item);
                }
            }
        }
        for (QGraphicsItem *item : itemsToRemove) {
            scene->removeItem(item);
            delete item;  // Освобождаем память
        }

        // Удаляем вершину и связанные с ней ребра из матрицы смежности
        adjacencyMatrix.removeAt(vertexToRemove);
        for (int i = 0; i < adjacencyMatrix.size(); ++i) {
            adjacencyMatrix[i].removeAt(vertexToRemove);
        }

        // Обновляем граф на основе обновленной матрицы смежности
        createGraphFromAdjacencyMatrix(scene, adjacencyMatrix);
    }

    const QVector<QVector<int>>& getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }


    const QVector<QVector<int>>& getWMatrix() const
    {
        return WMatrix;
    }

    QVector<QVector<int>>& getMatrix()
    {
        return adjacencyMatrix;
    }

    class KosarajuAlgorithm
    {
    public:
        QVector<QVector<int>> transposeGraph(const QVector<QVector<int>>& graph)
        {
            QVector<QVector<int>> transposedGraph(graph.size(), QVector<int>(graph.size(), 0));
            for (int i = 0; i < graph.size(); ++i)
            {
                for (int j = 0; j < graph.size(); ++j)
                {
                    transposedGraph[j][i] = graph[i][j];
                }
            }
            return transposedGraph;
        }

        void depthFirstSearch(int vertex, const QVector<QVector<int>>& graph, QVector<bool>& visited, QVector<int>& stack)
        {
            visited[vertex] = true;
            for (int i = 0; i < graph.size(); ++i)
            {
                if (graph[vertex][i] != 0 && !visited[i])
                {
                    depthFirstSearch(i, graph, visited, stack);
                }
            }
            stack.append(vertex);
        }

        void depthFirstSearchUtil(int vertex, const QVector<QVector<int>>& graph, QVector<bool>& visited, QVector<int>& component)
        {
            visited[vertex] = true;
            component.append(vertex);
            for (int i = 0; i < graph.size(); ++i)
            {
                if (graph[vertex][i] != 0 && !visited[i])
                {
                    depthFirstSearchUtil(i, graph, visited, component);
                }
            }
        }

        QVector<QVector<int>> findStrongComponents(const QVector<QVector<int>>& graph)
        {
            //инициализация всех контейнеров, необходимых для хранения компонент
            QVector<QVector<int>> stronglyConnectedComponents;
            QVector<bool> visited(graph.size(), false);
            QVector<int> stack;

            for (int i = 0; i < graph.size(); ++i)
            {
                if (!visited[i])
                {
                    depthFirstSearch(i, graph, visited, stack); //заполняем стек при обходе графа в глубину
                }
            }

            //транспонируем граф - то есть меняем его направления между ребрами
            QVector<QVector<int>> transposedGraph = transposeGraph(graph);
            visited.fill(false); //очистка вектора

            while (!stack.isEmpty())
            {
                int vertex = stack.takeLast();
                if (!visited[vertex]) //для каждой непосещенной вершины
                {
                    QVector<int> component;
                    depthFirstSearchUtil(vertex, transposedGraph, visited, component);
                    //добавляю компоненты сильной связности в полный список
                    stronglyConnectedComponents.append(component);
                }
            }

            return stronglyConnectedComponents;
        }
    };


    //Алгоритм Косараджу (O(V^2)) т.к. транспонирование - v^2 + два dfs-прохода прямой и обратный v^2
    void kosarajuAlgorithm(QGraphicsScene *scene)
    {
        scene->clear();

        int numVertices = 6; //число вершин, положим 6

        //матрица весов и матрица смежности (хотя можно использовать только матрицу весов)
        QVector<QVector<int>> adjacencyMatrix;
        QVector<QVector<int>> weightsMatrix;

        const float edgeProbability = 0.45; // Пример значения вероятности появления ребра

        // Создание случайных матриц смежности и весов с учетом пониженной вероятности создания ребра
        QRandomGenerator generator;
        for (int i = 0; i < numVertices; ++i)
        {
            QVector<int> adjacencyRow;
            QVector<int> weightsRow;
            for (int j = 0; j < numVertices; ++j)
            {
                if (i == j) {
                    adjacencyRow.append(0); // Нет петлей
                    weightsRow.append(0); // Вес ребра к себе же - 0
                } else
                {
                    float randomProbability = generator.generateDouble(); // Генерация случайного числа от 0 до 1
                    if (randomProbability < edgeProbability)
                    { // Проверка по пороговому значению
                        int weight = generator.bounded(10) + 1; // Случайный вес от 1 до 10
                        adjacencyRow.append(1); // Устанавливаем ребро
                        weightsRow.append(weight); // Устанавливаем вес ребра
                    } else
                    {
                        adjacencyRow.append(0); // Нет ребра
                        weightsRow.append(0); // Вес ребра - 0
                    }
                }
            }
            adjacencyMatrix.append(adjacencyRow);
            weightsMatrix.append(weightsRow);
        }

        /*
        // Создание случайных матриц смежности и весов
        QRandomGenerator generator;
        for (int i = 0; i < numVertices; ++i)
        {
            QVector<int> adjacencyRow;
            QVector<int> weightsRow;
            for (int j = 0; j < numVertices; ++j)
            {
                if (i == j) {
                    adjacencyRow.append(0); // Нет петлей
                    weightsRow.append(0); // Вес ребра к себе же - 0
                } else {
                    int isConnected = generator.bounded(2); // Случайное значение 0 или 1 для наличия ребра
                    adjacencyRow.append(isConnected);
                    if (isConnected) {
                        int weight = generator.bounded(10) + 1; // Случайный вес от 1 до 10
                        weightsRow.append(weight);
                    } else {
                        weightsRow.append(0); // Если ребра нет, то 0 вес
                    }
                }
            }
            adjacencyMatrix.append(adjacencyRow);
            weightsMatrix.append(weightsRow);
        }*/



        QVector<QGraphicsEllipseItem*> nodes;

        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < numVertices; ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности и весов
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    // Рисуем ребро с весом
                    QGraphicsLineItem *edge = scene->addLine(
                        nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                        nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                        );
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(weightsMatrix[i][j]));
                    weightText->setPos((nodes[i]->pos().x() + nodes[j]->pos().x()) / 2, (nodes[i]->pos().y() + nodes[j]->pos().y()) / 2);
                }
            }
        }

        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    //Определяем координаты середины ребра - будем использовать qreal-типа для повышенной точности
                    qreal x1 = nodes[i]->pos().x() + 25;
                    qreal y1 = nodes[i]->pos().y() + 25;
                    qreal x2 = nodes[j]->pos().x() + 25;
                    qreal y2 = nodes[j]->pos().y() + 25;

                    //Рисуем ребро с помощью QPainterPath
                    QPainterPath path; //Qpainterpath позволяет рисовать сложные контуры на сцене
                    path.moveTo(x1, y1);
                    path.lineTo(x2, y2);

                    // Получаем координаты середины ребра
                    qreal midX = (x1 + x2) / 2;
                    qreal midY = (y1 + y2) / 2;

                    // Вычисляем угол наклона ребра
                    qreal angle = ::atan2(y2 - y1, x2 - x1);

                    //Рисуем галочку в середине ребра - изображение стрелки
                    QPainterPath arrowPath;
                    arrowPath.moveTo(midX + 10 * ::cos(angle - M_PI/6), midY + 10 * ::sin(angle - M_PI/6));
                    arrowPath.lineTo(midX, midY);
                    arrowPath.lineTo(midX + 10 * ::cos(angle + M_PI/6), midY + 10 * ::sin(angle + M_PI/6));

                    // Отображаем ребро и галочку
                    QGraphicsPathItem *edge = scene->addPath(path);
                    QGraphicsPathItem *arrow = scene->addPath(arrowPath);
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(weightsMatrix[i][j]));
                    weightText->setPos(midX, midY); // Показываем номер ребра в середине отрезка
                }
            }
        }

        //Начало алгоритма для уже изображенного графа
        KosarajuAlgorithm algorithm;
        QVector<QVector<int>> strongComponents = algorithm.findStrongComponents(adjacencyMatrix);


        //по вектору сильно связанных компонент прохожу и вывожу их всех в консоль
        for (int i = 0; i < strongComponents.size(); ++i)
        {
            qDebug() << "Strongly Connected Component" << i << ":";
            for (int j = 0; j < strongComponents[i].size(); ++j)
            {
                qDebug() << strongComponents[i][j];
            }
        }
    }



    //Алгоритм Форда-Фалкерсона

    QVector<int> fordFulkerson(QVector<QVector<int>>& weightsMatrix, int source, int sink)
    {
        int numVertices = weightsMatrix.size();
        QVector<QVector<int>> residualGraph = weightsMatrix; // Создаем остаточную сеть, изначально равную исходной сети
        QVector<int> parent(numVertices, -1);
        QVector<int> maxFlow(numVertices, 0);
        maxFlow[source] = INT_MAX;

        bool pathFound = true;
        while (pathFound) {
            pathFound = bfs(residualGraph, source, sink, parent);

            if (pathFound) {
                int pathFlow = INT_MAX;
                for (int v = sink; v != source; v = parent[v]) {
                    int u = parent[v];
                    pathFlow = std::min(pathFlow, residualGraph[u][v]);
                }

                for (int v = sink; v != source; v = parent[v]) {
                    int u = parent[v];
                    residualGraph[u][v] -= pathFlow;
                    residualGraph[v][u] += pathFlow;
                }

                maxFlow[sink] += pathFlow;
            }
        }

        return maxFlow;
    }

    bool bfs(QVector<QVector<int>>& residualGraph, int source, int sink, QVector<int>& parent) {
        int numVertices = residualGraph.size();
        QVector<bool> visited(numVertices, false);
        QVector<int> queue;

        visited[source] = true;
        queue.push_back(source);

        while (!queue.isEmpty()) {
            int u = queue.front();
            queue.pop_front();

            for (int v = 0; v < numVertices; ++v) {
                if (!visited[v] && residualGraph[u][v] > 0) {
                    queue.push_back(v);
                    visited[v] = true;
                    parent[v] = u;
                }
            }
        }

        return visited[sink];
    }

    void mainFordFulkerson(QGraphicsScene *scene)
    {
        scene->clear();


        int numVertices = 6; //число вершин, положим 6

        //матрица весов и матрица смежности (хотя можно использовать только матрицу весов)
        QVector<QVector<int>> adjacencyMatrix;
        QVector<QVector<int>> weightsMatrix;

        const float edgeProbability = 0.45; // Пример значения вероятности появления ребра

        // Создание случайных матриц смежности и весов с учетом пониженной вероятности создания ребра
        QRandomGenerator generator;
        for (int i = 0; i < numVertices; ++i)
        {
            QVector<int> adjacencyRow;
            QVector<int> weightsRow;
            for (int j = 0; j < numVertices; ++j)
            {
                if (i == j) {
                    adjacencyRow.append(0); // Нет петлей
                    weightsRow.append(0); // Вес ребра к себе же - 0
                } else
                {
                    float randomProbability = generator.generateDouble(); // Генерация случайного числа от 0 до 1
                    if (randomProbability < edgeProbability)
                    { // Проверка по пороговому значению
                        int weight = generator.bounded(10) + 1; // Случайный вес от 1 до 10
                        adjacencyRow.append(1); // Устанавливаем ребро
                        weightsRow.append(weight); // Устанавливаем вес ребра
                    } else
                    {
                        adjacencyRow.append(0); // Нет ребра
                        weightsRow.append(0); // Вес ребра - 0
                    }
                }
            }
            adjacencyMatrix.append(adjacencyRow);
            weightsMatrix.append(weightsRow);
        }

        /*
        // Создание случайных матриц смежности и весов
        QRandomGenerator generator;
        for (int i = 0; i < numVertices; ++i)
        {
            QVector<int> adjacencyRow;
            QVector<int> weightsRow;
            for (int j = 0; j < numVertices; ++j)
            {
                if (i == j) {
                    adjacencyRow.append(0); // Нет петлей
                    weightsRow.append(0); // Вес ребра к себе же - 0
                } else {
                    int isConnected = generator.bounded(2); // Случайное значение 0 или 1 для наличия ребра
                    adjacencyRow.append(isConnected);
                    if (isConnected) {
                        int weight = generator.bounded(10) + 1; // Случайный вес от 1 до 10
                        weightsRow.append(weight);
                    } else {
                        weightsRow.append(0); // Если ребра нет, то 0 вес
                    }
                }
            }
            adjacencyMatrix.append(adjacencyRow);
            weightsMatrix.append(weightsRow);
        }*/



        QVector<QGraphicsEllipseItem*> nodes;

        // Создаем узлы графа в случайных позициях
        for (int i = 0; i < numVertices; ++i)
        {
            int x = rand() % 800 + 50; // Генерируем случайные координаты для x
            int y = rand() % 800 + 50; // Генерируем случайные координаты для y
            QGraphicsEllipseItem *node = scene->addEllipse(0, 0, 50, 50);
            node->setPos(x, y);
            nodes.append(node);

            QGraphicsSimpleTextItem *text = scene->addSimpleText(QString::number(i)); // Добавляем номер вершины
            text->setPos(x + 20, y + 60); // Позиционируем номер относительно вершины
        }

        // Создаем ребра графа на основе матрицы смежности и весов
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    // Рисуем ребро с весом
                    QGraphicsLineItem *edge = scene->addLine(
                        nodes[i]->pos().x() + 25, nodes[i]->pos().y() + 25,
                        nodes[j]->pos().x() + 25, nodes[j]->pos().y() + 25
                        );
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(weightsMatrix[i][j]));
                    weightText->setPos((nodes[i]->pos().x() + nodes[j]->pos().x()) / 2, (nodes[i]->pos().y() + nodes[j]->pos().y()) / 2);
                }
            }
        }

        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    //Определяем координаты середины ребра - будем использовать qreal-тип для повышенной точности
                    qreal x1 = nodes[i]->pos().x() + 25;
                    qreal y1 = nodes[i]->pos().y() + 25;
                    qreal x2 = nodes[j]->pos().x() + 25;
                    qreal y2 = nodes[j]->pos().y() + 25;

                    //Рисуем ребро с помощью QPainterPath
                    QPainterPath path; //Qpainterpath позволяет рисовать сложные контуры на сцене
                    path.moveTo(x1, y1);
                    path.lineTo(x2, y2);

                    // Получаем координаты середины ребра
                    qreal midX = (x1 + x2) / 2;
                    qreal midY = (y1 + y2) / 2;

                    // Вычисляем угол наклона ребра
                    qreal angle = ::atan2(y2 - y1, x2 - x1);

                    //Рисуем галочку в середине ребра - изображение стрелки
                    QPainterPath arrowPath;
                    arrowPath.moveTo(midX + 10 * ::cos(angle - M_PI/6), midY + 10 * ::sin(angle - M_PI/6));
                    arrowPath.lineTo(midX, midY);
                    arrowPath.lineTo(midX + 10 * ::cos(angle + M_PI/6), midY + 10 * ::sin(angle + M_PI/6));

                    // Отображаем ребро и галочку
                    QGraphicsPathItem *edge = scene->addPath(path);
                    QGraphicsPathItem *arrow = scene->addPath(arrowPath);
                    QGraphicsSimpleTextItem *weightText = scene->addSimpleText(QString::number(weightsMatrix[i][j]));
                    weightText->setPos(midX, midY); // Показываем номер ребра в середине отрезка
                }
            }
        }

        //Начало алгоритма для уже изображенного графа
        QVector<int> maxFlow = fordFulkerson(weightsMatrix, 0, 5);
        for (int i = 0; i < maxFlow.size(); ++i) {
            qDebug() << "Max flow from source to vertex" << i << ": " << maxFlow[i];
        }


    }



    void depthFirstSearchForKosaraju(const QVector<QVector<int>> &adjacencyMatrix, int nodeIndex, QVector<bool> &visited, QVector<int> &finishTimes)
    {
        visited[nodeIndex] = true;
        for (int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            if (!visited[i] && adjacencyMatrix[nodeIndex][i] == 1)
            {
                depthFirstSearchForKosaraju(adjacencyMatrix, i, visited, finishTimes);
            }
        }
        finishTimes.prepend(nodeIndex); // Добавляем вершину в начало списка при завершении обхода
    }

    QVector<QVector<int>> transposeGraph(const QVector<QVector<int>> &adjacencyMatrix)
    {
        int n = adjacencyMatrix.size();
        QVector<QVector<int>> transposed(n, QVector<int>(n, 0));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                transposed[i][j] = adjacencyMatrix[j][i];
            }
        }
        return transposed;
    }

    void showStronglyConnectedComponents(const QVector<QVector<int>> &stronglyConnectedComponents)
    {
        QString message = "Strongly Connected Components:\n";
        for (const auto& component : stronglyConnectedComponents)
        {
            for (int node : component)
            {
                message += QString::number(node) + "#";
            }
            message += "\n";
        }

        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
    }



};







int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //пример вычисления времени через класс QElapsedTimer

    //QElapsedTimer timer;
    //timer.start();

    ////GraphWidget graphWidget;
    ////graphWidget.show();

    //qint64 elapsed = timer.nsecsElapsed();
    //qDebug() << "Time elapsed:" << elapsed << "nanoseconds";



    QWidget window;
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    // Запрос количества вершин у пользователя
    bool ok;
    int n = QInputDialog::getInt(nullptr, "Введите количество вершин", "Количество вершин: (1 - заготовленный пример для графа)", 0, 0, 1000, 1, &ok);
    if (!ok) return 0; // Если пользователь отменил ввод, завершаем программу

    //Создается новый виджет - экземпляр класса для построения графов(n)
    GraphWidget *graphWidget = new GraphWidget(n);

    QWidget *controlPanel = new QWidget;
    QVBoxLayout *controlLayout = new QVBoxLayout(controlPanel);

    //Добавляем тут кнопки, метки и текстовые блоки на панель виджета
    QTextEdit *textBlock1 = new QTextEdit(" DFS: (O(V+E)) - Обход неориентированного невзвешенного графа в глубину: проход от начальной вершины до конечной по одной ветке.");
    QTextEdit *textBlock2 = new QTextEdit(" BFS: (O(V+E)) - вид обхода графа с концепцией расширения(прозходим все вершины с 1-уровня до последнего.");
    QTextEdit *textBlock3 = new QTextEdit(" DFS-forest: (O(V+E)*k) - набор деревьев, каждое их которых представляет собой компоненту сильной связности. Каждая вершина графа либо принадлежит \
    какому-то дереву DFS-леса, либо нет. Компонента сильной связности - максимальные по включении сильно связные подграфы, т.е. существует путь из V1 в Vn");
    QTextEdit *textBlock4 = new QTextEdit(" Kosaraju: (O(V^2)) - алгоритм для поиска компонент сильной связности через двойной dfs-проход и транспонирование графа");
    QTextEdit *textBlock5 = new QTextEdit(" Kruskal & Prime: O(ElogV) & O(V^2) - алгоритмы для построения минимального остовного дерева во взвешенном связном графе\
Прима добавляет к основному дереву ребра с минимальным весом, связывающие дерево с новой вершиной. Прост и очень эффективен. Отличия между ними в способе подбора ребер: крускала выбирает по возрастанию\
ребра и проверяет не образуется ли цикл, а прима постепенно добавляет к выбранной вершине ребра с минимальным весом.");
     QTextEdit *textBlock6 = new QTextEdit("Bellman-Ford: O(V*E) - алгоритм для нахождения всех кратчайших путей между вершиной p1-вершиной и всеми другими вершинами.");
    QLabel *label2 = new QLabel("LAB_2");
    QPushButton *button1 = new QPushButton("DFS");
    QPushButton *button2 = new QPushButton("DELETE");
    QPushButton *button3 = new QPushButton("BFS");
    QPushButton *button5 = new QPushButton("BFS-B-TREE");
    QPushButton *button4 = new QPushButton("DFS-forest");
    QPushButton *button6 = new QPushButton("Kosaraju");
    QPushButton *button7 = new QPushButton("Kruskal");
    QPushButton *button8 = new QPushButton("Prime");
    QPushButton *button9 = new QPushButton("Bellman-Ford");
    QPushButton *button11 = new QPushButton("Time-comparison");
    QPushButton *button10 = new QPushButton("Очистить сцену");
    QPushButton *button12 = new QPushButton("Ford-Fulkerson");


     controlLayout->addWidget(button1);
     controlLayout->addWidget(button3);
     controlLayout->addWidget(button5);
     controlLayout->addWidget(button2);
     controlLayout->addWidget(button4);
     controlLayout->addWidget(button6);
     controlLayout->addWidget(button7);
     controlLayout->addWidget(button8);
     controlLayout->addWidget(button9);
     controlLayout->addWidget(button11);
     controlLayout->addWidget(button12);
     controlLayout->addWidget(textBlock1);
     controlLayout->addWidget(textBlock2);
     controlLayout->addWidget(textBlock3);
     controlLayout->addWidget(textBlock4);
     controlLayout->addWidget(textBlock5);
     controlLayout->addWidget(textBlock6);
     controlLayout->addWidget(label2);
     controlLayout->addWidget(button10);

    splitter->addWidget(graphWidget);
    splitter->addWidget(controlPanel);

    //добавляем на основной макет виджет-разделитель splitter - то есть
    //с разделением в вертикальную либо горизонтальную полосу
    mainLayout->addWidget(splitter);



    //Метод сигналов и слотов для обработки событий, происиходящих в приложении
    //Обрабатываем сигналы с нажатий на кнопки, добавленные на главный макет выше

    //сигнал clicked связывается со слотом button с помощью лямбда-выражения, тело
    //которой заключено в фигурных скобках. Лямбда-выражение здесь нужно, чтобы писать функцию "на лету"
    //без отдельной реализациии. [=] указывает на захват всех переменных по значению(то есть изменения внутри
    //выражения никак не отразятся на внешние данные

    //DFS - обход графа
    QObject::connect(button1, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        graphWidget->createGraphFromAdjacencyMatrix(graphWidget->scene(), matrix);
    });

    //BFS - обход графа
    QObject::connect(button3, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        graphWidget->createGraphFromAdjacencyMatrixBFS(graphWidget->scene(), matrix);
    });

    //DFS-лес - построение леса -
    QObject::connect(button4, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        graphWidget->depthFirstForest(graphWidget->scene(), matrix);
    });

    //Алгоритм Косараджу
    QObject::connect(button6, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        graphWidget->kosarajuAlgorithm(graphWidget->scene());
    });

    //Алгоритм Форда-Фалкерсона
    QObject::connect(button12, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        graphWidget->mainFordFulkerson(graphWidget->scene());
    });

   //Алгоритм Крускала
    QObject::connect(button7, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
         const QVector<QVector<int>>& Wmatrix = graphWidget->getWMatrix();
        graphWidget->createWeightedGraphFromAdjacencyMatrix(graphWidget->scene(), matrix, Wmatrix);
    });


    //Алгоритм Прима
    QObject::connect(button8, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
         const QVector<QVector<int>>& Wmatrix = graphWidget->getWMatrix();
        graphWidget->createWeightedGraphFromAdjacencyMatrixPrim(graphWidget->scene(), matrix, Wmatrix);
    });

    //Сравнение по времени для одного и того же графа
    QObject::connect(button11, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        const QVector<QVector<int>>& Wmatrix = graphWidget->getWMatrix();
        graphWidget->TimeComparisonKruskalPrim(graphWidget->scene(), matrix, Wmatrix);
    });

    //Алгоритм Беллмана-Форда
    QObject::connect(button9, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        const QVector<QVector<int>>& Wmatrix = graphWidget->getWMatrix();
        graphWidget->createWeightedGraphFromMatrix(graphWidget->scene(), matrix, Wmatrix);
    });



    QObject::connect(button10, &QPushButton::clicked, [=](){
       // const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        //graphWidget->createGraph(graphWidget->scene(), 3, 5);
        graphWidget->clearscene(graphWidget->scene());
    });

    QObject::connect(button5, &QPushButton::clicked, [=](){
        const QVector<QVector<int>>& matrix = graphWidget->getAdjacencyMatrix();
        graphWidget->createBinaryTreeWithBFS(graphWidget->scene(), 20);
    });



    QObject::connect(button2, &QPushButton::clicked, [=](){
       QVector<QVector<int>>& matrix = graphWidget->getMatrix();
        graphWidget->removeVertexAndUpdateGraph(graphWidget->scene(), matrix, 0);
   });



    window.show();

    return app.exec();
}

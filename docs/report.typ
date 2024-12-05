
#set text(lang: "pt", 12pt)
#set heading(numbering: "1.")
#set par(justify: true)
#show link: set text(fill: blue)

// ------------- Header -------------
// Título no centro;
// Numeração das páginas alternada entre esquerda e direita.
#set page(header: context {
  align(center)[
    *Introdução à Inteligência Artificial*
    #context {
      let loc = here().page()
      if calc.even(loc) {
        align(left)[#counter(page).display("— 1 —")]
      } else if loc > 1 {
        align(right, counter(page).display("— 1 —"))
      }
    }
  ]
})

#align(center)[
  #text(20pt)[*Trabalho Prático I - 2024/2*] \
  Igor Lacerda Faria da Silva
]

= Introdução

O Trabalho Prático I de Introdução à Inteligência Artificial consistiu na implementação (em C++) de 5 algoritmos para cálculo de distância (exploração de espaço de busca) em mapas de um jogo simples. Os 5 algoritmos foram: _Breadth First Search_ (BFS), _Iterative Deepening Search_ (IDS), _Uniform Cost Search_ (UCS), Busca Gulosa (_Greedy_) e A\* (A-Star ou A-Estrela). A função heurística escolhida para os algoritmos que dependem dela (_Greedy_ e A\*) foi a *distância de Manhattan*. O repositório deste trabalho pode ser encontrado neste #link("https://github.com/igorlfs/tp1-iia")[link].

A documentação está divida da seguinte maneira: esta breve introdução descreve o que foi realizado, a @aedsm descreve a modelagem do programa, entrando nos detalhes dos algoritmos e estruturas de dados; a @heu, por sua vez, foca na heurística utilizada e, por fim, a @anaq é uma análise experimental dos diversos algoritmos implementados.

// • Apresentação das estruturas usadas e da modelagem dos componentes da busca (estado, função sucessora, etc);
// • Breve descrição das principais diferenças entre os algoritmos.
= Algoritmos, Estruturas de Dados e Modelagem <aedsm>

Sem dúvidas, a principal estrutura de dados do trabalho foi uma matriz de `double`, com os pesos das posições do mapa. Outras estruturas são específicas dos algoritmos: a maioria dos algoritmos usa um _heap_ (`priority_queue` do C++) para controlar qual será o próximo estado da busca, exceto pela BFS, que uma fila (`queue`) e a IDS, que usa uma pilha (`stack`). No mais, as estruturas restantes são estruturas padrões de C++, como vetores (`vector`) e pares ordenados (`pairs`).

== Formulação do Problema

Os 5 componentes da formulação do problema foram:

+ *Estados*: posições na matriz, com os peso associados
+ *Estado Inicial*: posição inicial, da entrada
+ *Sequência de Ações*: subir, descer, ir para esquerda ou para direita
+ *Teste do Objetivo*: posição final atingida
+ *Custo da Solução*: soma dos custos pelo qual a busca passou por

A função sucessora recebe uma das ações e faz o movimento da posição atual para a nova posição correspondente.

== Algoritmos

A seguir, uma breve descrição das principais diferenças entre os algoritmos, baseada na descrição de cada um. A BFS é usada como base e os outros algoritmos são vistos como "incrementos".

=== BFS

A BFS é um algoritmo relativamente simples. Dado um nó inicial, sua vizinhança é colocada na fila (primeiro a entrar é o primeiro a sair) e os nós são visitados na ordem em que foram inseridos, recursivamente. Obviamente, nós inválidos ou já visitados são excluídos da busca.

=== IDS

A IDS é uma DFS aplicada repetida diversas vezes, para profundidades cada vez maiores, até que o objetivo seja alcançado, ou o limite de profundidade seja atingido. A DFS é uma busca muito semelhante à BFS, a única diferença é que é usada uma pilha para se gerenciar os nós (ou seja, o primeiro a entrar é o último a sair). Além disso, como a busca da IDS tem a profundidade limitada, é necessário checar se a profundidade máxima daquela iteração foi atingida.

=== UCS

A UCS é também muito similar aos algoritmos anteriores. A diferença aqui é que usado um _heap_, que prioriza o nó de menor custo até então. Para que isso possa ser feito de maneira eficiente, é importante manter em memória uma matriz com o custo de cada posição.

=== _Greedy_

A busca gulosa é semelhante à UCS, pois também usa um _heap_ (apesar de não precisar de matriz de custos). A ideia é seguir pelo "melhor" caminho, mas usando uma aproximação definida por uma heurística (mais detalhes na @heu). Na busca gulosa, é explorado o "caminho que _parece_ melhor neste momento".

=== A\*

Por fim, o A-Estrela é uma combinação da busca gulosa com a UCS, que considera a soma dos custos gerados nestes algoritmos. A ideia é fazer uma busca que sempre é ótima, como na UCS, mas que é rápida porque é guiada pela heurística.

== Outras decisões de implementação

Presume-se que sempre existe um caminho de A (início) para B (objetivo). Caso algum desses nós tenha custo infinito, o programa é encerrado. Na implementação da IDS, a profundidade máxima foi definida como $W*H$.

// • Especificação das heurísticas utilizadas. Elas são admissíveis? Por quê?
= Heurísticas <heu>

A heurística escolhida foi a distancia de Manhattan. Ela é bem simples, pois é a soma soma da diferença absoluta das coordenadas. É por causa dessa simplicidade que ela é admissível: como o custo mínimo (por nó) é 1, o melhor custo é, na situação ideal, é justamente a distancia de Manhattan: deslocar-se $|x_i - x_f|$ unidades na horizontal e $|y_i - y_f|$ na vertical. É claro que esse é o cenário ideal, em que não existem impedimentos no meio do caminho e existe um caminho composto exclusivamente por nós de valor 1. De qualquer modo, a heurística nunca é mais cara do que o custo real para o objetivo e, portanto, pode-se dizer que ela é admissível.

// • Análise quantitativa comparando os algoritmos com relação ao número de estados expandidos e tempo de execução à medida que o ponto final se distancia do ponto inicial. Apresente tabelas e/ou gráficos comparativos.
// • Discussão dos resultados obtidos.
= Análise Quantitativa e Discussão <anaq>

Os 2 mapas (`floresta.map` e `cidade.map`) de exemplo disponibilizados via _Moodle_ foram usados para se realizar um _benchmarking_ dos algoritmos. De antemão, vale ressaltar que a ordem dos operadores é um fator muito importante no tempo de execução, especialmente da IDS. Com isso em mente, as comparações vão incluir os casos simétricos -- ou seja, invertendo o nó de início e o nó objetivo. Além disso, na execução dos experimentos, a `-O3`, de otimização do compilador, foi habilitada.

== Tempo de Execução <time>

Para avaliar o tempo de execução, foram propostas 5 pares de coordenadas em cada mapa. Como são dois mapas e a simetria é levada em conta, foram realizados 20 execuções por mapa.

=== Cidade

Como este mapa possui menos estados inválidos, o início do mapa foi fixado em (0, 0) e, os destinos, foram da forma $(2^i-1, 2^i-1)$, com $i$ variando de 4 até o limite do mapa, que gera a coordenada (255, 255). Para estes casos, os algoritmos _Greedy_ e BFS são extremamente rápidos, sendo que, boa parte do tempo de execução está associada a algum _overhead_ e não ao tempo de processamento dos estados propriamente ditos. A segunda "classe" de algoritmos é composta pelos algoritmos UCS e A\*: na teoria, o A\* deveria ser mais rápido, mas para os casos considerados nesta seção, não houve diferença significativa: ambos ficaram na faixa de dezenas de milissegundos para a maior instância, não ultrapassando 60ms.

O único algoritmo que apresentou um comportamento interessante foi a IDS. Na @ids-time-city, o caso base é até bem comportado, mas vale destacar que ele demorou muito mais do que os outros algoritmos: para a maior instância, seu tempo de execução ficou próximo de meio segundo. O caso em que a execução termina em (0, 0) é ainda mais intrigante, pois, além de demorar (ainda) mais, a entrada "intermediária" teve um tempo de execução muito semelhante ao caso mais distante, ambos beirando os 2.5s. O porquê disso será melhor discutido na @nee.

#figure(
  image("plots/ids-time-city.png"),
  caption: [Tempo de execução da IDS no mapa Cidade.],
) <ids-time-city>

De forma geral, não se pode dizer que o tempo escala proporcionalmente à distância de Manhattan. Esse efeito foi observado, em menor escala, com os algoritmos rápidos também.

=== Floresta

A Floresta é um mapa mais denso, então não é possível selecionar os pontos usando-se a "estratégia de base 2" da seção anterior. No entanto, ela foi usada de base para se definir o ponto de início (17, 0), que é o canto superior mais à esquerda. Os pontos de destino escolhidos foram: (17, 16), (35, 31), (102, 63), (132, 127) e (208, 255). A escolha se deu a partir do deslocamento dos pontos da estratégia anterior para posições próximas que não estivesse bloqueadas.

No geral, o comportamento foi bem semelhante ao outro mapa, mas a velocidade dos algoritmos foi ainda mais acentuada devido ao espaço de busca reduzido. Foi possível separar os algoritmos em dois grupos: os ultrarrápidos e a IDS. De fato, o tempo dos ultrarrápidos não excedeu 10ms nas instâncias escolhidas. A IDS, por outro lado, apresentou o comportamento que pode ser visto na @ids-time-forest.

#figure(
  image("plots/ids-time-forest.png"),
  caption: [Tempo de execução da IDS no mapa Floresta.],
) <ids-time-forest>

Como as coordenadas $x$ e $y$ dos pontos são diferentes, foi adotado o $y$ como base para a distância (para aproximar consistência com o gráfico anterior, da @ids-time-city). Devido à alta quantidade de caminhos bloqueados neste mapa, a execução de destaque foi a de distância 63 (comportamento consistente em ambas direções), com tempo de execução elevado para sua distância. De fato, neste mapa também não parece existir relação clara entre a distância e o tempo de execução.

Há, ainda, a questão do _overhead_, que pode ter influenciado na análise de tempo como um todo. Como o programa é rápido, a execução em ambos os mapas está sujeita a grandes variações considerando fatores externos, como o _load_ do sistema operacional. Uma análise mais aprofundada exigiria mapas maiores.

== Número de Estados Expandidos <nee>

O número de estados expandidos não pode ser obtido diretamente da saída esperada do programa. É possível _plotar_ o caminho, mas isso limita significativamente o poder de análise. Por exemplo, usando apenas a comparação do caminho, os algoritmos UCS e A\* são indistinguíveis, pois ambos sempre são ótimos. Tendo isso em vista, essa seção possui uma breve análise preliminar, que foca em algumas execuções específicas, comparando os caminhos.

Depois, é introduzida uma variação do programa, que rastreia quais estados foram expandidos, permitindo extrair sua totalidade. Como essa operação introduz um certo _overhead_ e é incompatível com a saída especificada para o programa, essa variação foi considerada exclusiva desta análise (por isso ela não foi mencionada na seção anterior).

=== Caminhos <paths>

Para analisar os caminhos, foram selecionadas duas execuções da @time: $(0, 0) arrow (127, 127)$ e o caminho reverso, no mapa Cidade.

#figure(
  image("plots/paths-front.svg"),
  caption: [Caminhos, iniciando em (0, 0) e terminando em (127, 127).],
) <paths-front>

#figure(
  image("plots/paths-back.svg"),
  caption: [Caminhos, iniciando em (127, 127) e terminando em (0, 0).],
) <paths-back>

A grande diferença das figuras é que, a IDS, no caminhamento reverso, explora muito mais estados devido à ordem das ações. Isso acontece porque a configuração padrão favorece posições que começam no canto superior esquerdo, pois a região explorada inicialmente é "para baixo e para a direita". É por isso que o tempo de execução da IDS foi tão elevado na seção @time.

A ordem das ações acaba impactando em alguns dos outros algoritmos também, mas em menor grau. Por exemplo, a BFS fez um caminho quase perfeitamente simétrico. Outro ponto interessante é que os algoritmos ótimos não fizeram exatamente o mesmo caminho na "volta", apesar de terem feito na "ida". Isso acontece porque existe mais de um caminho ótimo e, devido à ordem das operações, houve um trecho (próximo a $P = (40, 40)$) em que o A\* e a UCS divergiram.

=== Estados

Para finalizar, a análise de estados explorados. Como mencionado no início da seção, foi feita uma modificação no programa, para que ele pudesse produzir dados mais relevantes para esta análise. Em suma, a modificação troca o custo da solução pela quantidade de estados explorados e o caminho gerado por uma lista com todos os nós visitados. Novamente, a IDS introduz certa dificuldade: o mesmo nó é visitado diversas vezes, o que contribui consideravelmente para seu tempo de execução. No entanto, a abordagem de somente contar os nós visitados não é capaz de detectar isso.

Além disso, no A\* também podem acontecer repetições. Apesar disso, nesta seção preferiu-se apenas comparar os nós visitados, porque algumas conclusões importantes já foram deduzidas nas outras análises: independentemente das repetições, a IDS visita muito mais nós (ver @paths-back). De fato, as questões ainda não respondidas podem ser exploradas justamente a partir da exploração da quantidade "líquida" de estados visitados.

Por exemplo: o quão melhor é o A\* em relação à UCS? A partir da discussão na @paths, não era possível extrair uma resposta. Para responder a essa pergunta, o experimento da @paths foi repetido com a modificação proposta aqui. O resultado para os caminhos "base" é exibido na @visited-ucs-astar. Em termos absolutos, o A\* visitou 8078 estados, enquanto a UCS visitou um total de 23367 estados. Ou seja, nesse caso específico, a busca do A\* visitou aproximadamente $1/3$ dos estados da busca da UCS.

#figure(
  image("plots/visited-nodes-ucs-astar.svg"),
  caption: [Nós visitados, iniciando em (0, 0) e terminando em (127, 127).],
) <visited-ucs-astar>

De forma mais geral, os experimentos da seção de tempo (@time) foram repetidos e os gráficos, com a contagem de estados visitados, podem ser encontrados nas figuras a seguir.

Primeiramente, no mapa Cidade, fica evidente a eficiência do _Greedy_, que visita pouquíssimos estados. Na maioria dos casos, o A\* deixa a busca bem mais rápida que o UCS, como avaliado na @visited-ucs-astar. No entanto, para as instâncias maiores, o ganho é pequeno. Não foi encontrada uma explicação para o fato de a BFS e a UCS possuírem curvas tão semelhantes. Outra situação interessante foi a IDS ter uma redução tão drástica na maior busca (para o caminho de "ida").

#figure(
  image("plots/city-visited-base.png"),
  caption: [Nós visitados, no mapa Cidade.],
) <visited-city-base>

#figure(
  image("plots/city-visited-reverse.png"),
  caption: [Nós visitados, no mapa Cidade, caminho reverso.],
) <visited-city-rev>

Comparando-se ambos os gráficos, é possível observar que quase todos os algoritmos "pioram" (visitam mais estados) na busca reversa, exceto quando ela é colossal (distância 255), momento em que já não há mais tanta diferença. O mapa Floresta é discutido a seguir.

#figure(
  image("plots/forest-visited-base.png"),
  caption: [Nós visitados, no mapa Floresta.],
) <visited-forest-base>

#figure(
  image("plots/forest-visited-reverse.png"),
  caption: [Nós visitados, no mapa Floresta, caminho reverso.],
) <visited-forest-base>

Fica clara a relação entre o tempo de execução e o número de estados expandidos: na @ids-time-forest, observou-se que para a execução de distância 63, o tempo de execução foi particularmente elevado. Nas figuras acima, é possível notar que neste caso, a maioria dos algoritmos explora "desproporcionalmente" o espaço de busca (especialmente na "volta").

Tal qual no outro mapa, UCS e BFS são muito próximas em termos de estados explorados. Vale notar que os algoritmos tem um comportamento consistente no caso base e que a análise de mais pontos poderia ser interessante suavizar o formato "ondular" do gráfico. Para o caminho reverso é mais complicado de se extrair informações: tanto a UCS como a BFS atingem um pico logo no início, e ficam por volta dele, mas cada um dos outros algoritmos é diferente. Para o _Greedy_, por exemplo, o maior "contorno" que o algoritmo teve que fazer, provavelmente estava na primeira metade da busca. Já o A\* tem um comportamento semelhante ao outro mapa, com rendimentos decrescentes (em relação à UCS).

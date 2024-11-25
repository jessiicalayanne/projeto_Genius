# Miniprojeto 

## 1º - Jogo Genius
Implemente um jogo de memória inspirado no clássico "Genius", utilizando LEDs e botões.

O jogo consistirá em criar um sistema embarcado que apresentará sequências aleatórias de luzes (LEDs) que deverá ser reproduzida pelo usuário pressionando os botões na mesma ordem. Observe a função random para geração de números pseudo aleatórios: https://docs.arduino.cc/language-reference/en/functions/random-numbers/random/

A complexidade do jogo aumentará à medida que o jogador avança nas rodadas, exigindo maior concentração e memória para acompanhar as sequências geradas. O sistema pode conter alguma limitação de tamanho máximo de sequencia gerada - esse número pode ser grande o suficiente para que um humano com habilidades medianas de memória nunca consiga vencer o jogo.

## Requisitos
1) O jogo deverá ter no mínimo 4 LEDs e consequentemente 4 botões;
2) O jogo deve começar com uma sequência inicial de LEDs que acende e apaga em uma ordem específica - você pode escolher qual o tamanho dessa sequencia inicial;
3) Após a sequência inicial, o jogador deve tentar reproduzir a sequência pressionando os botões na ordem correta.
4) A sequência inicial de LEDs deve aumentar gradualmente em complexidade à medida que o jogador avança no jogo. Cada rodada do jogo deve aumentar em pelo menos um elemento da sequência.
5) O jogador deve receber feedback imediato após cada tentativa de reproduzir a sequência. O nível atual do jogo deverá ser indicado em um display de 7 segmentos. O jogo deverá iniciar no nível 1 e a cada sequência acertada pelo jogador, o nível deverá ser incrementada. Caso o jogador cometa algum erro, o jogo deverá retornar para o nível 1.
6) O jogador deve ser capaz de iniciar um novo jogo em qualquer momento (abandonar uma partida).

## Avaliação
1) Código no GitHub (condição obrigatória para a avaliação);
2) Funcionalidade do projeto (atendimento aos requisitos propostos) - 80 pontos
3) Confiabilidade e organização e clareza do código - 20 pontos

O jogo deve ser robusto o suficiente para lidar com entradas de usuário esperadas e inesperadas sem falhas ou travamentos.
O código-fonte deve ser bem organizado, com uma estrutura clara e modular, facilitando futuras atualizações e manutenções.
As variáveis, funções e métodos devem ter nomes que descrevam claramente sua finalidade e funcionalidade. 
Nomes de funções e métodos devem indicar claramente o que eles fazem e o que é esperado como retorno.
Cada função deve ter uma única responsabilidade, realizando apenas uma operação ou tarefa específica.
Deve-se preferir o uso de espaçamento consistente, indentação apropriada e comentários relevantes para facilitar a compreensão do código.
Deve-se evitar a duplicação de código, procurando sempre reutilizar funções e componentes existentes quando possível.

## Montangem 
![image](https://github.com/jessiicalayanne/projeto_Genius/blob/main/tinkercad%20genius.png?raw=true)

## Busca na Tabela Hash

- Existe um problema, a adição de dois elementos iguais na minha estrutura de dados.
    - A partir deste ponto, ao inserir um novo elemento na minha tabela, será verificado cada elemento a partir da posição pré-definida, com um número máximo de passos.

### Encadeamento separado

- Novo método para tratar colisões
- Cada posição da nossa Tabela Hash é uma lista encadeada.
- Toda vez que inserir o elemento, será calculada a tabela hash.
    - Será necessário percorrer todos os elementos da lista encadeada para verificar se não há um elemento igual.


```c
typedef struct node
{
    Item item;
    node *next;
} node;
```

- Dependendo do número de colisões, a inserção, busca e remoção poderá assumir complexidade linear.
    - Portanto, é necessário uma boa estratégia para definir o chaveamento da sua tabela. Como por exemplo, a utilização de números primos.

```c
#define MOD 4133
#define KEY(value) value % MOD
```

Para acessar o código da implementação, clique [aqui](./e_sep.c)

### Lidando com chaves de String

- Criação de um conjunto de pesos para cada caractere da string, com o objetivo de evitar colisões
- Por exemplo, temos dois valores aleatórios e cada vez, algum deles assumiria um valor novo.
    - Nesse caso, temos `a` e `b`
    - Os valores aleatórios iniciais precisam ser armazenados para realizar a busca

```c
int hashuniversal(char *key, int M) 
{
    int a = 314159;
    int b = 271828;
    int h = 1;

    for(; *key != 0; key++) 
    {
        a = (a + b *(*key)) % M;
        h = (h*a) % M; 
    }

    return h;
}
```
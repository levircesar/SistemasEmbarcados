# SistemasEmbarcados

Repositorio para o trabalho da disciplina

## Como executar os arquivos

Primeiro tenha o contiki-ng instalado em sua maquina, em seguida abra o local do arquivo e use o comando:

```
make
```
Isso criara a pasta <i>builds</i> e será possivel executar o comando a seguir

```
./helloworld.native
```
Pronto, o resultado aparecerá no terminal.

Questoes:
<br>
<b>1 - Criar dois processo sendo um principal que recebe os valores dos sensores e toma uma decisão do que fazer, e o outro um processo secundário que pega os valores dos sensores e envia para o processo principal via eventos. Para o processo secundário, gerar valores aleatótios a cada determinado tempo (por exemplo a cada 10 segundos) e enviar para o processo principal.</b>
<p>Ao todo temos 3 processos se comunicando via eventos e em arquivos separados: </p>
<ul>
    <li>Principal</li>
     <li>sensores</li>
      <li>blinkled</li>
</ul>

<br>
<b>2 - Criar três processos um principal e dois secundários. O processo principal irá receber uma informação (string em hexadecimal) atravéz de um buffer stático, simulando o recebimento de uma informação pela porta serial. Dependendo da informação que tenha nesse buffer, o processo principal deverá chamar um dos dois processos secundários para processar esses dados do buffer principal. O processo sencundário deve retornar com um conjunto de dados no formato hexadecmal em um buffer para o processo principal.</b>

<br>
<b>3 - Criar três processos um principal e dois secundários. O processo principal irá receber uma informação atravéz de um buffer stático, simulando o recebimento de uma informação pela porta serial. Dependendo da informação que tenha nesse buffer, o processo principal deverá chamar um dos dois processos secundários para processar esses dados do buffer principal. Até aqui o mesmo da questão anterior. Contudo, para essa atividade, cada processo secundário deve executar sua função de callback pelo menos 5 vezes antes de retornar com uma informação válida no formato hexadecimal em um buffer para o processo principal.</b>
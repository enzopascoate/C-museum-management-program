Olá! Este reposiório consiste em um pequeno projeto que elaborei durante o segundo semestre de minha graduação no curso de Análise de Sistemas.

Programado em C, consiste em uma aplicação de console criada com o intuito de auxiliar a bilheteria de museu em suas atividades cotidianas (tema escolhido pela universidade). 


![image](https://github.com/enzopascoate/MMS-museum-management-system/assets/137375620/d824ebb6-73a6-442b-9bde-0beca1b623a4)


Dentre as capacidades deste software, estão: 

+ Oferecer diferentes niveis de permissão conforme as credenciais inseridas (login e senha de administrador e usuário);
  
+ Efetuar venda de ingressos capaz de lidar com um ou mais ingressos de uma vez e diferenciar cada um por seu gênero (inteiro, meia-entrada, isento).
  
+ Atribuir códigos de identificação únicos aos ingressos e salvá-los em um arquivo .csv para posterior validação.
  
+ Validar ingressos por meio de seus códigos de identificação, indicando ao usuário se determinado ingresso é válido, ou não. Uma vez que um ingresso é validado, este é removido do arquivo .csv.
  
+ Efetuar cadastro e salvamento de clientes, registrando seus Nomes, Sobrenomes, Datas de Nascimento, Gênero e Cidade de Residência e salvando como entradas de ID único em um arquivo .csv.
  
+ Exibição de Dados de Cadastro salvos, permitindo fornecendo ao usuário duas opções:
  
           - Exibir Registro Geral: Exibe na tela, de forma ordenada conforme número de entrada, todas as entradas no arquivo .csv que armazena os cadastros de clientes.
  
           - Busca filtrada: Permite ao usuário elaborar buscas filtradas com base em um campo específico. Usuários podem buscar exclusivamente por: Número de Entrada, Nome, Sobrenome, Ano de Nascimento,
           Gênero e Cidade de Residência. Desta maneira, são exibidas na tela apenas as entradas cujos campo selecionado corresponde ao valor pesquisado.

+ Deleção de Dados (ADMINISTRADOR): A função de Deleção de Dados, reservada ao administrador, possibilita o apagamento de um cadastro a partir de seu Número de Entrada, removendo-o do arquivo .csv.


+ Credenciais de usuário:
   - Login: user - Password: userpassword
+ Credenciais de Administrador:
   - Login: admin - Password: adminpassword

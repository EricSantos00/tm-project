# Objetivos
- Fazer com que este projeto rode utilizando a base de arquivos do Client WYD Global/KR de Versão 7.69+

# O que foi realizado
- Alterado as Estruturas para ler os arquivos de forma correta
- Alterado a forma em que o cliente le o arquivo sn.bin, sendo nescessário utilizar o bloco de notas para editar o mesmo.
- Foi adicionado uma tool de conversão da itemlist
- Foi adicionado o cliente base para o funcionamento do mesmo
- Foi adicionado a leitura do Lang.txt
- Foi adicionado inicialização dos componentes da arena real @SkyDrive
- Foi adicionado os slots novos 16 e 17, deve ser alterado no servidor o MAX_EQUIP para 18
- Foi adicionado algumas descompilações na pasta Descompilations
- Deve se utilizar o visual studio 2022
- Atualizando o projeto para v769.2
- Alterado a estrutura da itemlist para v769.2
- Adicionado Mission System, deve ser revisado antes de usar
- Adicionado MountData Bin e Csv nos conversores
- Deve ser adicionado a leitura da nova itemlist no servidor, use a base do conversor de itemlist
- Adicionado .c da versão v769.2



# TMProject

Este projeto é baseado em uma descompilação do cliente do jogo With Your Destiny. 
Nós não reindividicamos nenhum direito autoral do projeto. Este projeto foi criado apenas para fins de estudo sendo todos os direitos reservados exclusivamente e inteiramente a Hanbitsoft.

Este código é uma descompilação fiel ao original, isto é, o código que aqui consta não remete ao que nós, desenvolvedores, faríamos. Como o projeto como um todo já foi completamente finalizado, tendo todas as funções necessárias para que o jogo seja jogável, o mesmo pode ser alterado como quiser.

## Compilação
O projeto pode ser compilado apenas para Windows utilizando Visual Studio (o projeto está preparado para a versão 2019, mas o mesmo não há limitação quanto a versão mínima ou máxima). 

A compilação para x64 é possível, basta que seja utilizado a dependência para x64 do DirectX assim como corrigir problemas quanto a compilação para esta arquitetura.

## Dependências

### Visual Studio
Para compilar o projeto você precisará ter o Visual Studio 2022 com os seguintes componentes instalados:
- Desenvolvimento para desktop com C++
- ATL do C++ para a versão da toolchain que está sendo utilizada

A única dependência externa do projeto é o DirectX porém o mesmo está incluida no repositório e devidamente configurada.

## Bugs
Este projeto é uma descompilação e o mesmo pode e contém problemas. 

Sinta-se a vontade para reportá-los e abrir um pull request para o projeto (esperamos que você faça isso). 

### Pull-request
Para manter o código mais organizado, o padrão de código que consta atualmente deverá ser seguido, como por exemplo:
- Variáveis com estilo hungarian, e.g: pPointer, nInt, bBoolean, sz para sized string e etc.
- Nome de classes em PascalCase
- entre outros...

Como não temos um documento que dite todas as regras, caso surja uma dúvida, procure no código algum exemplo do que você está tentando fazer.

## Contribuidores
Este projeto foi desenvolvido por:
- Eric Santos (SKEWED)
- Wed Souza (FREEDOM)
- Kevin Kouketsu (shepher)

# General Public License:

The code is under the [GNU GPL v3](https://www.gnu.org/licenses/gpl-3.0.html), so you can be feel free to study and contribute.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

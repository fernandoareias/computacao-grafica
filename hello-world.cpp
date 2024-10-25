#include <windows.h>  // Inclui a biblioteca Windows API para utilizar funções específicas do sistema operacional Windows

// Declara a função principal para aplicativos Windows (substitui o uso de 'main' em aplicações de console)
int APIENTRY WinMain(HINSTANCE hInstance,      // 'hInstance' é um identificador para a instância do aplicativo atual
                     HINSTANCE hPrevInstance,  // 'hPrevInstance' é um identificador para a instância anterior do aplicativo (geralmente NULL)
                     LPSTR lpCmdLine,          // 'lpCmdLine' contém a linha de comando usada para iniciar o aplicativo
                     int nCmdShow)             // 'nCmdShow' indica como a janela do aplicativo será exibida (minimizada, maximizada, etc.)
{
    // Cria uma caixa de mensagem com o texto "Hello World", o título "Message" e sem ícones ou botões especiais
    MessageBox(NULL, "Hello World", "Message", 0);

    return 0;  // Retorna 0 para indicar que o programa terminou sem erros
}

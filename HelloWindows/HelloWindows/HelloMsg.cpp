#define WIN32_LEAN_AND_MEAN // Reduz o tamanho da biblioteca Windows, excluindo APIs menos usadas para tornar a compilação mais eficiente
#include <windows.h>        // Inclui a biblioteca principal da API do Windows

// Definindo _In_ e _In_opt_ como vazios para evitar erro de compilação no MinGW
#define _In_
#define _In_opt_

// Declaração do protótipo da função de tratamento de mensagens (callback) da janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Função principal de aplicativos Windows
int APIENTRY WinMain(_In_ HINSTANCE hInstance,     // Identificador da instância do aplicativo atual
    _In_opt_ HINSTANCE hPrevInstance, // Identificador da instância anterior (geralmente NULL)
    _In_ LPSTR lpCmdLine,         // Linha de comando usada para iniciar o aplicativo
    _In_ int nCmdShow)            // Modo de exibição inicial da janela (minimizada, maximizada, etc.)
{
    HWND hwnd;           // Identificador para a janela criada
    MSG msg;             // Estrutura para armazenar mensagens de eventos
    WNDCLASS wndclass;   // Estrutura para definir a classe da janela (aparência e comportamento)

    // Definindo as propriedades da janela
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  // Redesenha a janela quando o tamanho horizontal ou vertical é alterado
    wndclass.lpfnWndProc = WinProc;            // Ponteiro para a função de tratamento de mensagens (WinProc)
    wndclass.cbClsExtra = 0;                   // Número de bytes extras após a estrutura da classe da janela (não usado)
    wndclass.cbWndExtra = 0;                   // Número de bytes extras após a estrutura da janela (não usado)
    wndclass.hInstance = hInstance;            // Instância do aplicativo atual
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Ícone padrão para a janela
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);   // Cursor padrão (seta)
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Cor de fundo branca
    wndclass.lpszMenuName = NULL;              // Sem menu para a janela
    wndclass.lpszClassName = "AppWindow";      // Nome da classe da janela

    // Registrando a classe da janela
    if (!RegisterClass(&wndclass))  // Retorna 0 se falhar ao registrar a classe
    {
        MessageBox(NULL, "Erro na criação da janela!", "Aplicação", MB_ICONERROR); // Exibe mensagem de erro
        return 1; // Termina o programa com erro
    }

    // Criando a janela
    hwnd = CreateWindow(
        "AppWindow",                // Nome da classe da janela
        "Minha Aplicação",          // Título da janela
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // Estilo da janela com bordas e botões padrão
        CW_USEDEFAULT,              // Posição X padrão
        CW_USEDEFAULT,              // Posição Y padrão
        CW_USEDEFAULT,              // Largura padrão
        CW_USEDEFAULT,              // Altura padrão
        NULL,                       // Sem janela mãe (janela principal)
        NULL,                       // Sem menu para a janela
        hInstance,                  // Instância do aplicativo
        NULL                        // Sem parâmetros adicionais
    );

    // Verificando se a janela foi criada com sucesso
    if (!hwnd)  // Se a criação da janela falhar
    {
        MessageBox(NULL, "Falha ao criar a janela!", "Erro", MB_ICONERROR); // Exibe mensagem de erro
        return 1; // Termina o programa com erro
    }

    // Exibe a janela e atualiza seu conteúdo
    ShowWindow(hwnd, nCmdShow); // Define o modo de exibição da janela
    UpdateWindow(hwnd);         // Solicita a atualização da janela (força seu redesenho)

    // Loop de mensagens para o aplicativo Windows (gerencia eventos)
    while (GetMessage(&msg, NULL, 0, 0))  // Lê a próxima mensagem da fila
    {
        TranslateMessage(&msg);   // Traduz mensagens (por exemplo, combina teclas)
        DispatchMessage(&msg);    // Envia a mensagem para a função de tratamento de janela
    }

    return (int)msg.wParam;  // Retorna o código de saída do programa
}

// Função de processamento de mensagens para a janela
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:           // Mensagem de encerramento da janela
        PostQuitMessage(0);    // Envia uma mensagem para terminar o loop de mensagens
        break;
    }

    // Processa qualquer outra mensagem usando a função padrão
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

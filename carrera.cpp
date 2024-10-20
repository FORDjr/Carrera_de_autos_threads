#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <chrono>
#include <random>
#include <atomic>
#include <algorithm>

// Definiciones de colores 
#define RESET   "\033[0m" 
#define GREEN   "\033[32m"


// Estructura que representa a cada auto en la carrera

struct Auto {
    std::string nombre;          // Nombre único del auto 
    int distancia_recorrida = 0; // Distancia que ha recorrido el auto
    int lugar_llegada = 0;       // Posición en la que llegó el auto
};





std::mutex mtx;                      // Mutex para sincronizar la salida en consola
std::atomic<int> posicion_actual(1); // Variable que controla el orden de llegada de los autos
int M;                               // Distancia total de la carrera 
int N;                               // Número de autos


// Función para el avance de los autos en la carrera
void correr(Auto &carro) {
    
    // Inicialización de generadores de números aleatorios
    std::random_device rd; 
    std::mt19937 gen(rd());

    // Distribuciones para avance y velocidad
    std::uniform_int_distribution<> dist_avance(1, 10);     // Avance entre 1 y 10 metros
    std::uniform_int_distribution<> dist_velocidad(100, 500); // Velocidad entre 100 y 500 ms

    // Bucle principal: el auto avanza hasta completar la distancia total de la carrera 
    while (carro.distancia_recorrida < M) {
        
        // Generar avance aleatorio y actualizar distancia recorrida del auto
        int avance = dist_avance(gen);
        carro.distancia_recorrida += avance;

        if (carro.distancia_recorrida >= M) {
            carro.distancia_recorrida = M;

            // Bloquear mutex para imprimir de forma segura
            mtx.lock();
            std::cout << GREEN << carro.nombre << " avanza " << avance << " metros y termina la carrera en el lugar " << posicion_actual << "!!!" << RESET << std::endl;
            // Registrar lugar de llegada y actualizar posición actual
            carro.lugar_llegada = posicion_actual++;
            mtx.unlock();

            break; // Salir del bucle al terminar la carrera
        } else {
            
            // Imprimir avance actual
            mtx.lock();
            std::cout << carro.nombre << " avanza " << avance << " metros (total: "
                        << carro.distancia_recorrida << " metros)" << std::endl;
            mtx.unlock(); //desbloquear mutex
        }

        // Generar velocidad aleatoria y pausar el hilo
        int velocidad = dist_velocidad(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(velocidad));
    }
}


int main(int argc, char *argv[]) {
    // Verificar que se proporcionen los argumentos necesarios
    if (argc != 3) {
        std::cout << "Error: se esperaba siguiente formato: './carrera <distancia_total> <numero_autos>'" << std::endl;
        return 1;
    }

    // Convertir argumentos a enteros para M y N
    M = std::stoi(argv[1]); // Distancia total de la carrera
    N = std::stoi(argv[2]); // Número de autos

    // Mostrar información inicial
    std::cout << "Distancia total carrera: " << M << " metros" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    // Crear vectores para autos y hilos
    std::vector<Auto> autos(N);         // Vector de autos
    std::vector<std::thread> hilos;     // Vector de hilos

    // Asignar nombres a los autos
    for (int i = 0; i < N; ++i) {
        autos[i].nombre = "Auto" + std::to_string(i);
    }

    // Crear y lanzar los hilos para cada auto
    for (int i = 0; i < N; ++i) {
        hilos.push_back(std::thread(correr, std::ref(autos[i])));
    }

    // Esperar a que todos los hilos terminen
    for (auto &hilo : hilos) {
        hilo.join();
    }

    // Mostrar resultados finales
    mtx.lock(); // Bloquear mutex para impresión segura
    std::cout << "\nLugar\tAuto\n------------------" << std::endl;

    // Ordenar los autos según el lugar de llegada
    std::sort(autos.begin(), autos.end(), [](const Auto &a, const Auto &b) {
        return a.lugar_llegada < b.lugar_llegada;
    });

    // Imprimir el orden de llegada
    for (const auto &carro : autos) {
        std::cout << carro.lugar_llegada << "\t" << carro.nombre << std::endl;
    }
    mtx.unlock(); // Desbloquear mutex

    return 0;
}


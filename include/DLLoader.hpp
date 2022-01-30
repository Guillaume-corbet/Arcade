/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <iostream>
#include <dlfcn.h>

template<typename T>
class DLLoader {
    public:
        DLLoader() {};
        T *getInstance(const char *lib, void **handler)
        {
            void *handle = dlopen(lib, RTLD_LAZY);
            if (!handle) {
                std::cerr << "Erreur ouverture de la lib : " << lib << std::endl << dlerror() << std::endl;
                exit(84);
            }
            T *(*func)();
            *(void **) (&func) = dlsym(handle, "entryPoint");
            if (func == NULL) {
                std::cerr << "Erreur lecture de la lib : " << lib << std::endl << dlerror() << std::endl;
                exit(84);
            }
            (*handler) = handle;
            return (func());
        };
    protected:
    private:
};

#endif /* !DLLOADER_HPP_ */

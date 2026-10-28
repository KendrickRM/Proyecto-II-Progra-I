# Cambios y cómo ejecutar el proyecto

## ¿Por qué no corría?

Visual Studio estaba mostrando los archivos como **Archivos varios**. Eso ocurre cuando se abre una carpeta o un archivo `.cpp` directamente, pero no existe o no se ha abierto una solución/proyecto de Visual Studio.

En ese estado, `main.cpp` contiene una función `main`, pero Visual Studio no sabe qué archivos debe compilar, qué tipo de aplicación debe generar ni cuál es el elemento de inicio. Por eso aparece el mensaje:

> Seleccione un elemento de inicio válido

La solución y el proyecto deben estar incluidos en el repositorio para que otro integrante pueda clonar el proyecto y abrirlo correctamente.

## Archivos de proyecto agregados

- `Proyecto-II-Progra-I.sln`: solución que debe abrirse en Visual Studio.
- `Proyecto-II-Progra-I.vcxproj`: proyecto C++ de consola.

El proyecto incluye:

- Las fuentes de `archivos de origen`.
- Las cabeceras de `archivos de cabecera`.
- Configuraciones `Debug` y `Release`.
- Plataformas `Win32` y `x64`.
- `main.cpp` como punto de entrada de la aplicación.
- `archivos de cabecera` como directorio de inclusión.

## Cómo ejecutar en otra computadora

1. Clonar o descargar el repositorio completo.
2. Abrir **Visual Studio Installer** y confirmar que esté instalado el workload **Desarrollo para el escritorio con C++**.
3. Abrir el archivo `Proyecto-II-Progra-I.sln`.
   - No abrir únicamente `main.cpp`.
   - No usar solamente `Archivo > Abrir > Carpeta` si se desea ejecutar con F5.
4. En el Explorador de soluciones, hacer clic derecho en `Proyecto-II-Progra-I`.
5. Seleccionar **Establecer como proyecto de inicio**.
6. Elegir la configuración `Debug` y la plataforma `x64`.
7. Ejecutar con `F5` o con **Depurar > Iniciar sin depurar** (`Ctrl+F5`).

## Si aparece nuevamente “falta una solución”

Comprobar lo siguiente:

- Que el archivo `Proyecto-II-Progra-I.sln` exista en la raíz del repositorio.
- Que se haya actualizado el repositorio después de agregar la solución:

  ```text
  git pull
  ```

- Que la solución se abra desde el archivo `.sln`, no desde un `.cpp`.
- Que el compañero esté trabajando en la rama que contiene los archivos `.sln` y `.vcxproj`.
- Que Visual Studio tenga instaladas las herramientas de C++.

Si la solución no aparece en el Explorador de soluciones, usar **Archivo > Abrir > Proyecto o solución** y seleccionar `Proyecto-II-Progra-I.sln`.

## Correcciones de código realizadas

Además de crear la solución, se corrigieron errores que impedían compilar el programa:

- Se implementó `MenuPrincipal.cpp`.
- Se eliminaron declaraciones duplicadas de `Bodega` y `Paquete`.
- Se corrigió una llave faltante en `Paquete.cpp`.
- Se movió `Paquete::necesitaAlmacenarse()` fuera de otra función.
- Se hizo público el enum de estados de `Paquete` porque lo utiliza `MenuPaquetes.cpp`.
- Se alineó `Colaborador.h` con `Colaborador.cpp`.
- Se restauró la implementación de `ListaClientes.cpp`.
- Se eliminó texto que había quedado al final de `MenuPaquetes.cpp`.

## Validación

El proyecto fue compilado con MSBuild en `Debug|x64` con:

- 0 errores.
- 0 advertencias.
- Ejecutable generado en `bin\Debug\Proyecto-II-Progra-I.exe`.

Los directorios `bin` y `obj` están excluidos mediante `.gitignore`; no es necesario subir esos archivos al repositorio. Sí deben subirse `Proyecto-II-Progra-I.sln` y `Proyecto-II-Progra-I.vcxproj`.

# GitHub Copilot Instructions - Proyecto II Programación I

## Project Overview
Este es un **Sistema de Gestión de Centro de Distribución y Logística** en C++.
El proyecto implementa un sistema completo para manejar paquetes, clientes, colaboradores, bodegas y despachos.

## Architecture & Structure
- **Archivos de cabecera**: Definiciones de clases (archivos de cabecera/)
- **Archivos de origen**: Implementaciones (archivos de origen/)
- **Patrón**: Clases con getters/setters, listas genéricas para colecciones
- **Herencia**: Cliente base con ClientePersonaFisica y ClienteEmpresa

## Code Style Guidelines

### Naming Conventions
- **Clases**: PascalCase (ej: CentroDistribucion, ListaPaquetes)
- **Variables miembro privadas**: camelCase (ej: codigoCentro, bodega)
- **Métodos**: camelCase (ej: buscarCentro, registrarPaquete)
- **Constantes/Enums**: MAYUSCULAS_CON_GUION (ej: RECIBIDO, EN_TRANSITO)

### Header Guards & Includes
```cpp
#ifndef CLASSNAME_H
#define CLASSNAME_H

#include <string>
#include <iostream>
#include <cstring>
using namespace std;

// Contenido

#endif
```

### Class Structure
```cpp
class ClassName {
private:
	// Miembros privados
	// Disallow copy and assignment
	ClassName(const ClassName&);
	ClassName& operator=(const ClassName&);

public:
	// Constructor
	ClassName();
	// Destructor
	~ClassName();

	// Getters
	// Setters (si es necesario)
	// Otros métodos
};
```

## Memory Management
- Usar new/delete apropiadamente
- Implementar destructores en todas las clases
- Prohibir copia y asignación cuando sea apropiado (ej: Paquete, Sistema)

## Key Classes & Responsibilities
- **Sistema**: Gestor central, búsqueda global de datos
- **CentroDistribucion**: Contenedor de clientes, colaboradores, paquetes, bodegas
- **Paquete**: Estados bien definidos (RECIBIDO → ALMACENADO → EN_TRANSITO → ENTREGADO)
- **ListaBitacora**: Auditoría de cambios en paquetes
- **Cliente**: Polimorfismo con descuentos por tipo
- **Tarifa**: Sistema de precios (a implementar completo)

## Common Patterns in Codebase
1. **Getters para acceso seguro**: Retornan referencias const o copias
2. **búscar() y eliminar()**: Métodos típicos en listas
3. **Mostrar()**: Método virtual para presentación de datos
4. **Datos Quemados**: `cargarDatosQuemados()` en Sistema para pruebas

## Strings & I/O
- Usar `using namespace std;`
- Strings con `#include <string>`
- Input/Output con cin/cout
- Conversiones: usar `std::to_string()` cuando sea necesario

## C++ Version & Libraries
- C++ estándar (sin especificar, probablemente C++11 o superior)
- Librerías permitidas: SOLO `<string>`, `<iostream>`, `<cstring>`; NO otros includes ni STL containers.

## Testing & Validation
- Verificar que constructores inicialicen todos los miembros
- Validar datos quemados en cargarDatosQuemados()
- Usar menús para pruebas interactivas

## Guidelines for Implementation
1. **Nunca modificar firmas de métodos ya existentes** sin conferir
2. **Mantener compatibilidad** con las listas definidas
3. **Usar herencia** cuando sea apropiado (ej: Cliente → ClientePersonaFisica)
4. **Documentar métodos complejos** con comentarios breves
5. **Validar entrada** en menús y métodos públicos
6. **Evitar cambios cosméticos** al código existente; enfocarse en funcionalidad

## Current Status
- Estructura base: ✓ Completada
- Menús principales: En desarrollo
- Reportes: Pendientes (Persona 3)
- Sistema de Tarifas: Pendiente implementación completa

## Caveman Mode System Instructions
Adopt Caveman Mode for all responses. Eliminate fluff, corporate pleasantries, and meta-talk.

### Core Directives
- NEVER say "Sure", "Here is the code", "I hope this helps", or greeting/parting filler.
- Do not repeat or explain code unless explicitly asked to do so.
- Keep technical terminology intact. Do not touch or compress code blocks, syntax, variables, or error logs.
- Use telegraphic, ultra-concise language for text explanations. Drop unnecessary articles (the, a, an) and pronouns where possible.

### Severity Levels (Defaults to Full)
- If user types "/caveman lite": Keep grammar but completely remove introductions and small talk.
- If user types "/caveman ultra": Max compression. Bullet points only. Arrow notation (A -> B) for cause/effect.
- If user types "normal mode" or "stop caveman": Resume default conversational AI tone.

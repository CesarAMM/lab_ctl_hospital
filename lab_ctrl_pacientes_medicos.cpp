#include <fstream>
#include <iostream>
#include <vector>
#include <string>
//#include <ctype.h>
//#include <stdio.h> 
//#include <stdlib.h>

using namespace std;

struct Medico{
  int codigo;
  string nombre;
  string apellido;
  string telefono;
  string especialidad;
  string fehca_inicio;
};

struct Paciente{
  int codigo;
  string nombre;
  string apellido;
  string telefono;
  int edad;
  float peso;
};

struct Cita{
  int codigo;
  int codigo_paciente;
  int codigo_medico;
  string dianostico;
  string fecha_cita;
};
//! Constantes para realizar las consultas
const string DB_MEDICO = "DB_Medico.dat";
const string DB_PACIENTE = "DB_Paciente.dat";
const string DB_CITA = "DB_Cita.dat";
//TODO: Funcion para ronar espacios para crear tablas
string fn_espacios(int PLTamanio, int PLValor){
	int PLEspacio = 0;
	string PLTexto = "";
	PLEspacio = PLValor - PLTamanio;
	for (int i = 0; i < PLEspacio; i++){
		PLTexto = PLTexto + " ";
	}
	return PLTexto;
}

//TODO: Funcion para separar un texto en arreglo
vector<string> split(string str, string separador){
	int posIni = 0, posFin = 0;
	string splitted;
	vector<string> resultado;
	while (posFin >= 0){
		posFin = str.find(separador, posIni);
		splitted = str.substr(posIni, posFin - posIni);
		posIni = posFin + 1;
		resultado.push_back(splitted);
	}
	return resultado;
}

// MANEJO DE FICHEROS
void fn_ingresar_medico(vector<Medico> &VMedicos, string VDataBase){
  ofstream fich(VDataBase);
  if(!fich){
    cout << "<< [ERROR] NO SE PUEDE ABRIR EL ARCHIVO ["<<VDataBase<<"] >>\n\n";
    exit(EXIT_FAILURE);
  }

  for (Medico VLMedico : VMedicos){
    fich << VLMedico.codigo <<","<<VLMedico.nombre<<","<<VLMedico.apellido<<","<<VLMedico.telefono<<","<<VLMedico.especialidad<<","<<VLMedico.fehca_inicio<< endl;
  }
  
  fich.close();
}

int fn_abrir_archivo_medico(vector<Medico> &VMedicos){
  string VLTexto;
  vector<string> VLTextos;
  Medico VLMedico;
  ifstream fich(DB_MEDICO);
  if (!fich.is_open()){
    cout << "<< [ERROR] 2 NO SE PUEDE ABRIR EL ARCHIVO >>\n\n";
    exit(EXIT_FAILURE);
  }
  while (fich >> VLTexto){
    VLTextos = split(VLTexto, ",");
    VLMedico.codigo = stoi(VLTextos[0]);;
    VLMedico.nombre = VLTextos[1];
    VLMedico.apellido = VLTextos[2];
    VLMedico.telefono = VLTextos[3];
    VLMedico.especialidad = VLTextos[4];
    VLMedico.fehca_inicio = VLTextos[5];
    VMedicos.push_back(VLMedico);
  }
  return VLMedico.codigo;
}

int fn_abrir_archivo_paciente(vector<Paciente> &VLDaotos){
  string VLTexto;
  vector<string> VLTextos;
  Paciente VLPacienmte;
  ifstream fich(DB_PACIENTE);
  if(!fich.is_open()){
    cout <<"<< [ERROR] NO SE PUEDE ABRIR EL ARCHIVO ["<<DB_PACIENTE<<"] >>\n\n";
    exit(EXIT_FAILURE);
  }
  while (fich >> VLTexto){
    VLTextos = split(VLTexto, ",");
    VLPacienmte.codigo = stoi(VLTextos[0]);
    VLPacienmte.nombre = VLTextos[1];
    VLPacienmte.apellido = VLTextos[2];
    VLPacienmte.telefono = VLTextos[3];
    VLPacienmte.edad = stoi(VLTextos[4]);
    VLPacienmte.peso = stof(VLTextos[5]);    
    VLDaotos.push_back(VLPacienmte);
  }
  
  return VLPacienmte.codigo;
}

void fn_ingresar_paciente(vector<Paciente> VLDatos){
  ofstream fich(DB_PACIENTE);
  if(!fich){
    cout << "<< [ERROR] NO SE PUEDE ABRIR EL ARCHIVO ["<<DB_PACIENTE<<"] >>\n\n";
    exit(EXIT_FAILURE);
  }
  for (Paciente VLPaciente : VLDatos){
    fich << VLPaciente.codigo <<","<<VLPaciente.nombre<<","<<VLPaciente.apellido<<","<<VLPaciente.telefono<<","<<VLPaciente.edad<<","<<VLPaciente.peso<<"\n";
  }
  
  fich.close();
}


int fn_abrir_archivo_cita(vector<Cita> &VLDaotos){
  string VLTexto;
  vector<string> VLTextos;
  Cita VLCita;
  ifstream fich(DB_CITA);
  if(!fich.is_open()){
    cout <<"<< [ERROR] NO SE PUEDE ABRIR EL ARCHIVO ["<<DB_CITA<<"] >>\n\n";
    exit(EXIT_FAILURE);
  }
  while (fich >> VLTexto){
    VLTextos = split(VLTexto, ",");
    VLCita.codigo =stoi(VLTextos[0]);
    VLCita.codigo_medico = stoi(VLTextos[1]);
    VLCita.codigo_paciente = stoi(VLTextos[2]);
    VLCita.fecha_cita = stoi(VLTextos[3]);
    VLCita.dianostico = VLTextos[4];
    VLDaotos.push_back(VLCita);
  }
  
  return VLCita.codigo;
}

void fn_ingresar_cita(vector<Cita> VLDatos){
  ofstream fich(DB_CITA);
  if(!fich){
    cout << "<< [ERROR] NO SE PUEDE ABRIR EL ARCHIVO ["<<DB_CITA<<"] >>\n\n";
    exit(EXIT_FAILURE);
  }
  for (Cita VLCita : VLDatos){
    fich << VLCita.codigo <<","<<VLCita.codigo_medico<<","<<VLCita.codigo_paciente<<","<<VLCita.fecha_cita<<","<<VLCita.dianostico<<"\n";
  }
  fich.close();
}
//PANTALLA
int fn_menu_principal(){

  int VLOpcion;
  cout << "**********************\n";
  cout << "**  MENU PRINCIPAL  **\n";
  cout << "**********************\n";
  cout << "** 1) Medicos       **\n";
  cout << "** 2) Pacientes     **\n";
  cout << "** 3) Citas         **\n";
  cout << "** 4) Salir         **\n";
  cout << "**********************\n";
  cout << ">> Ingrese una Opcion: ";
  cin >> VLOpcion;
  return VLOpcion;
}

int fn_menu_medicos(){
  int VLOpcion;
  cout << "*********************\n";
  cout << "**   MENU MEDICOS  **\n";
  cout << "*********************\n";
  cout << "** 1) Ingreso      **\n";
  cout << "** 2) Modificacion **\n";
  cout << "** 3) Consulta     **\n";
  cout << "** 4) Eliminar     **\n";
  cout << "** 5) Regresar     **\n";
  cout << "**********************\n";
  cout << ">> Ingrese una Opcion: ";
  cin >> VLOpcion;
  return VLOpcion;
}

int fn_menu_pacientes(){
  int VLOpcion;
  cout << "*********************\n";
  cout << "**  MENU PACIENTES **\n";
  cout << "*********************\n";
  cout << "** 1) Ingreso      **\n";
  cout << "** 2) Modificacion **\n";
  cout << "** 3) Consulta     **\n";
  cout << "** 4) Eliminar     **\n";
  cout << "** 5) Regresar     **\n";
  cout << "**********************\n";
  cout << ">> Ingrese una Opcion: ";
  cin >> VLOpcion;
  return VLOpcion;
}

int fn_menu_cita(){
  int VLOpcion;
  cout << "*********************\n";
  cout << "**    MENU CITAS   **\n";
  cout << "*********************\n";
  cout << "** 1) Ingreso      **\n";
  cout << "** 2) Modificacion **\n";
  cout << "** 3) Consulta     **\n";
  cout << "** 4) Eliminar     **\n";
  cout << "** 5) Regresar     **\n";
  cout << "**********************\n";
  cout << ">> Ingrese una Opcion: ";
  cin >> VLOpcion;
  return VLOpcion;
}

/* OPCIONES PARA MEDICOS */
void fn_ing_medico(){
  vector<Medico> VMedico;
  Medico VLMedico;
  int VLOpcion, VLSiguiente, VLConteo =0;
  cout << "************************\n";
  cout << "** INGRESO DE MEDICOS **\n";
  cout << "************************\n\n";
  VLConteo = fn_abrir_archivo_medico(VMedico);
  do{
    VLOpcion = 0;
    VLSiguiente = 0;

    cout << "-->> Nombre del Medico: ";
    cin >> VLMedico.nombre;
    cout << "-->> Apellido del Medico: ";
    cin >> VLMedico.apellido;
    cout << "-->> Telefono del Medico: ";
    cin >> VLMedico.telefono;
    cout << "--> Ingrese Especialidad:";
    cin >> VLMedico.especialidad;
    cout << "--> Ingrese fecha inicio (dd/mm/yyyy): ";
    cin >> VLMedico.fehca_inicio;
    cout << ">> Desea Guardar los datos Ingresados [0 = SI / 1 = NO]: ";
    cin >> VLOpcion;

    if(VLOpcion == 0){
      VLConteo++;
      VLMedico.codigo = VLConteo;
      VMedico.push_back(VLMedico);
    }
    
    cout << "--> Desea Agregar otro [0 = SI / 1 = NO]: ";
    cin >> VLSiguiente;
  }while(VLSiguiente != 1);
  fn_ingresar_medico(VMedico, DB_MEDICO);
}

void fn_ver_medicos(vector<Medico> VLMedicos){
  cout <<"| Codigo  | Nombre Medico            | Telefono  | Fecha      | Especialidad      |\n";
    cout <<"|---------|--------------------------|-----------|------------|-------------------|\n";
    for(Medico VMedico : VLMedicos){
      cout <<"| "<<VMedico.codigo<<fn_espacios(to_string(VMedico.codigo).length(), 8);
      cout <<"| "<<VMedico.nombre<<" "<<VMedico.apellido<<fn_espacios(VMedico.apellido.length() + VMedico.nombre.length() +1 , 25);
      cout <<"| "<<VMedico.telefono<<fn_espacios(VMedico.telefono.length(), 10);
      cout <<"| "<<VMedico.fehca_inicio<<fn_espacios(VMedico.fehca_inicio.length(), 11);
      cout <<"| "<<VMedico.especialidad<<fn_espacios(VMedico.especialidad.length(),18)<<"|\n";
    }
    cout <<"|---------|--------------------------|-----------|------------|-------------------|\n";
}

void fn_ver_paciente(vector<Paciente> VLDatos){
  cout <<"| Codigo  | Nombre Paciente          | Telefono  | Edad       | Peso      |\n";
  cout <<"|---------|--------------------------|-----------|------------|-----------|\n";
    for(Paciente VPaciente : VLDatos){
      cout <<"| "<<VPaciente.codigo<<fn_espacios(to_string(VPaciente.codigo).length(), 8);
      cout <<"| "<<VPaciente.nombre<<" "<<VPaciente.apellido<<fn_espacios(VPaciente.apellido.length() + VPaciente.nombre.length() +1 , 25);
      cout <<"| "<<VPaciente.telefono<<fn_espacios(VPaciente.telefono.length(), 10);
      cout <<"| "<<VPaciente.edad<<fn_espacios(to_string(VPaciente.edad).length(), 11);
      cout <<"| "<<VPaciente.peso<<fn_espacios(to_string(VPaciente.peso).length(),10)<<"|\n";
    }
    cout <<"|---------|--------------------------|-----------|------------|-------------------|\n";
}

void fn_ver_cita(vector<Cita> VLDatos){
  vector<Medico> VLMedicos;
  vector<Paciente> VLPacientes;
  string VTMedico, VTPaciente;
  bool VBMedico, VBPaciente;
  fn_abrir_archivo_medico(VLMedicos); // ir a traer a los medicos
  fn_abrir_archivo_paciente(VLPacientes); // ir a traer a los pacientes
  cout <<"| Codigo  | Nombre Paciente          | Nombre Medico            | Fecha Cita  | Dianostico\n";
  cout <<"|---------|--------------------------|--------------------------|-------------|--------------------------------\n";
    for(Cita VCita : VLDatos){
      VBMedico = false; 
      VBPaciente = false;
      VTMedico = ""; 
      VTPaciente = "";
      for (Medico VLMedico: VLMedicos){
        if(VLMedico.codigo == VCita.codigo_medico){
          VTMedico = VLMedico.nombre + " "+ VLMedico.apellido;  
          VBMedico =true;
          break;
        }
      }
      for (Paciente VLPaciente: VLPacientes){
        if(VLPaciente.codigo == VCita.codigo_paciente){
          VTPaciente = VLPaciente.nombre + " "+ VLPaciente.apellido;  
          VBPaciente = true;
          break;
        }
      }
      
      if(VBMedico && VBPaciente){
        cout <<"| "<<VCita.codigo<<fn_espacios(to_string(VCita.codigo).length(), 8);
        cout <<"| "<<VTPaciente<<fn_espacios(VTPaciente.length(), 25);
        cout <<"| "<<VTMedico<<fn_espacios(VTMedico.length(), 25);
        cout <<"| "<<VCita.fecha_cita<<fn_espacios(VCita.fecha_cita.length(), 12);
        cout <<"| "<<VCita.dianostico<<"|\n";
      }
    }
    cout <<"|---------|--------------------------|-----------|------------|-------------------|\n";
}

void fn_upd_medico(){
  vector<Medico> VLMedicos;
  int VLCantidad, VLCodigo, VLOPT;
  bool VLEncontrado;
  cout << "************************\n";
  cout << "** INGRESO DE MEDICOS **\n";
  cout << "************************\n\n";
  do  
  {
    VLCantidad = fn_abrir_archivo_medico(VLMedicos);
    VLEncontrado = false;
    fn_ver_medicos(VLMedicos);
    cout << "Ingrece 0 para regresar\n";
    cout << ">> Ingrese Codigo a modificar: "; cin >> VLCodigo;
    if(VLCodigo != 0){
      for(Medico &VMMedico : VLMedicos){
        if(VMMedico.codigo == VLCodigo){
          VLEncontrado = true;
          cout << "| Ingrese Nombre: "; cin >> VMMedico.nombre;
          cout << "| Ingrese Apellido: "; cin >> VMMedico.apellido;
          cout << "| Ingrese Telefono: "; cin >> VMMedico.telefono;
        }
      }
      if(!VLEncontrado){
        cout << " << [ERROR] CODIGO INGRESADO ["<<VLCodigo<<"] NO ENCONTRADO >>";
      }else{
        cout << "| Desa Guardar los Cambios [1 = SI / OTRO NUMERO = NO]: "; cin >> VLOPT;
        if(VLOPT == 1){
          fn_ingresar_medico(VLMedicos, DB_MEDICO);
          cout << "| << SE HAN GUARDADO LOS CAMBIOS >>\n\n";
          VLMedicos.clear();
        }
      }
    }
  } while (VLCodigo != 0);
}

void fn_sel_medico(){
  vector<Medico> VLMedicos;
  int VLCantidad = fn_abrir_archivo_medico(VLMedicos);
  fn_ver_medicos(VLMedicos);
}

void fn_sel_pacientes(){
  vector<Paciente> VLPacientes;
  int VLCantidad = fn_abrir_archivo_paciente(VLPacientes);
  fn_ver_paciente(VLPacientes);
}

void fn_sel_cita(){
  vector<Cita> VLCitas;
  int VLCantidad = fn_abrir_archivo_cita(VLCitas);
  fn_ver_cita(VLCitas);
}

void fn_del_medico(){
  vector<Medico> VLMedicos;
  int VLCantidad, VLCodigo, VLPost, VLOPT;
  bool VLEncontrado;
  do{
    VLCantidad = fn_abrir_archivo_medico(VLMedicos);
    fn_ver_medicos(VLMedicos);
    cout << "Ingrece 0 para regresar\n";
    cout << ">> Ingrese Codigo a modificar: "; cin >> VLCodigo;
    if(VLCodigo != 0){
      VLPost = 0;
      VLEncontrado = false;
      for (Medico VMedico : VLMedicos){
        if(VMedico.codigo == VLCodigo){
          VLEncontrado = true;
          break;
        }
        VLPost++;
      }
      if(!VLEncontrado){
        cout << "<< [ERROR] EL CONDIGO ["<<VLCodigo<<"] NO SE ENCONTRO >>";
      }else{
        cout << "| Desa Guardar los Cambios [1 = SI / OTRO NUMERO = NO]: "; cin >> VLOPT;
        if(VLOPT == 1){
          VLMedicos.erase(VLMedicos.begin() + VLPost);
          fn_ingresar_medico(VLMedicos, DB_MEDICO);
          cout << "| << SE HAN GUARDADO LOS CAMBIOS >>\n\n";
          VLMedicos.clear();
        }
      }
      
    }
  }while(VLCodigo != 0);
  
}

/* OPCIONES PARA PACIENTES */
void fn_ing_pacientes(){

}

void fn_upd_pacientes(){

}

void fn_del_pacientes(){

}

/* OPCIONES PARA PACIENTES */
void fn_ing_cita(){

}

void fn_upd_cita(){

}


void fn_del_cita(){

}

void fn_opt_medicos(){
  int VLOpcion;
  do{
    VLOpcion = fn_menu_medicos();
    switch (VLOpcion){
      case 1: fn_ing_medico(); break;
      case 2: fn_upd_medico(); break;
      case 3: fn_sel_medico(); break;
      case 4: fn_del_medico(); break;
      case 5:break;
      default: cout << "<<  [ERROR] OPCION INGRESADA ["<<VLOpcion<<"] ES INCORRECTA  >>\n\n"; break;
    }
  }while(VLOpcion != 5);
}

void fn_opt_pacientes(){
  int VLOpcion;
  do{
    VLOpcion = fn_menu_pacientes();
    switch (VLOpcion){
      case 1: fn_ing_pacientes(); break;
      case 2: fn_upd_pacientes(); break;
      case 3: fn_sel_pacientes(); break;
      case 4: fn_del_pacientes(); break;
      case 5:break;
      default: cout << "<<  [ERROR] OPCION INGRESADA ["<<VLOpcion<<"] ES INCORRECTA  >>\n\n"; break;
    }
  }while(VLOpcion != 5);
}

void fn_opt_citas(){
  int VLOpcion;
  do{
    VLOpcion = fn_menu_cita();
    switch (VLOpcion){
      case 1: fn_ing_cita(); break;
      case 2: fn_upd_cita(); break;
      case 3: fn_sel_cita(); break;
      case 4: fn_del_cita(); break;
      case 5:break;
      default: cout << "<<  [ERROR] OPCION INGRESADA ["<<VLOpcion<<"] ES INCORRECTA  >>\n\n"; break;
    }
  }while(VLOpcion != 5);
}

void pr_inicio_(){
  int VLOpcion = 0;
  do{
    VLOpcion = fn_menu_principal();
    switch (VLOpcion){
      case 1: fn_opt_medicos();   break;
      case 2: fn_opt_pacientes(); break;
      case 3: fn_opt_citas();     break;
      case 4: cout << "<< GRACIAS POR INGRESAR >>"; break;
      default: cout << "<< [ERROR] OPCION INGRESADA ["<<VLOpcion<<"] ES INCORRECTA >>\n\n"; break;
    }
  }while(VLOpcion != 4);
}

int main(int argc, char const *argv[])
{
  pr_inicio_();
  return 0;
}
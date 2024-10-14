/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package carroo;

/**
 *
 * @author User
 */
public class Carroo {

        //Atributos
    String nome;
    String marca;
    int ano;
    int velocidade;
    
    
    //Metodos
    public void acelarar(int aceleraçao) {
        velocidade+=aceleraçao;
        
    }
    public void freiar (int reduzir){
    velocidade-=reduzir;
    
    }
    public void buzinar(){
        System.out.println("Bibibi");
    }
}

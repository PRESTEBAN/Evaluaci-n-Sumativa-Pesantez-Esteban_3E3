import { Component } from '@angular/core';
import { Firestore, doc, setDoc, getDoc } from '@angular/fire/firestore';
import { ApiserviceService } from './../services/apiservice.service';
import { AngularFirestore } from '@angular/fire/compat/firestore';
@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  constructor(private afs: AngularFirestore,private api: ApiserviceService) {
  }

   // Primera tarjeta
  numberValue: number = 0;
  cardTitle: string = 'Pokemon Card';
  pokemonImage: string = '';
  pokemonTypes: string = '';
  searchPokemonID: number | undefined; 

  // Segunda tarjeta
  searchQuery: string = '';
  searchCardTitle: string = 'Search Result';
  searchPokemonImage: string = '';

  // Función para incrementar el número en el ion-input
  incrementInput() {
    if (this.searchPokemonID === undefined) {
      this.searchPokemonID = 1;
    } else if (this.searchPokemonID < 100) {
      this.searchPokemonID += 1;
    }
  }

  // Función para decrementar el número en el ion-input
  decrementInput() {
    if (this.searchPokemonID && this.searchPokemonID > 1) {
      this.searchPokemonID -= 1;
    }
  }

  // Función para buscar el Pokemon por su ID
  searchByPokemonID() {
    if (this.searchPokemonID) {
      this.getPokemonDataByID(this.searchPokemonID, false);
    }
  }

  // Función para obtener datos de un Pokémon por su ID
  getPokemonDataByID(id: number, isSearchCard: boolean) {
    try {
      this.api.getPokemonID(id).subscribe((response => {
        const pokemon = response.name;
        const types = response.types.map((type: any) => type.type.name);
  
        // Guardar solo un tipo en Firebase
        const typeToSave = types[0];
        this.savePokemonTypeToFirebase(typeToSave);
  
        if (isSearchCard) {
          this.searchCardTitle = pokemon;
          this.searchPokemonImage = response.sprites.front_default;
        } else {
          this.cardTitle = pokemon;
          this.pokemonImage = response.sprites.front_default;
          // Mostrar ambos tipos en la aplicación
          this.pokemonTypes = types.join(', ');
        }
      }));
    } catch (error) {
      console.log(error);
    }
  }
  
  
  savePokemonTypeToFirebase(type: string) {
    try {
      const pokemonRef = this.afs.collection('pokemones').doc('pokemon');
      pokemonRef.set({
        type: type
      }).then(() => {
        console.log(`Tipo de Pokémon actualizado en Firebase: ${type}`);
      }).catch(error => {
        console.error('Error al actualizar el tipo de Pokémon en Firebase:', error);
      });
    } catch (error) {
      console.log(error);
    }
  }

  // Función para resetear la búsqueda
  resetSearch() {
    this.searchQuery = '';
    this.searchCardTitle = 'Search Result';
    this.searchPokemonImage = '';
  }
}
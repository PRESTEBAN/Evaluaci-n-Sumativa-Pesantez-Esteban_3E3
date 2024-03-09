import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouteReuseStrategy } from '@angular/router';

import { IonicModule, IonicRouteStrategy } from '@ionic/angular';
import { environment } from '../environments/environment'; // Importa el entorno
import { HttpClientModule } from '@angular/common/http';

import { AppComponent } from './app.component';
import { AppRoutingModule } from './app-routing.module';

import { initializeApp, provideFirebaseApp } from '@angular/fire/app';
import { getFirestore, provideFirestore } from '@angular/fire/firestore';
import { AngularFirestoreModule } from '@angular/fire/compat/firestore'; 


@NgModule({
  declarations: [AppComponent],
  imports: [BrowserModule, IonicModule.forRoot(), AppRoutingModule,HttpClientModule, AngularFirestoreModule,
           provideFirebaseApp(() => initializeApp(environment.firebaseConfig)),
           provideFirestore(() => getFirestore()),
           provideFirebaseApp(() => initializeApp({"projectId":"pokedexpesantez","appId":"1:672419696322:web:e1eddab8e5f9ba12d6355b","storageBucket":"pokedexpesantez.appspot.com","apiKey":"AIzaSyCADIjF2BEYn4FvZL1FGwVb_Aux9KjWBJ8","authDomain":"pokedexpesantez.firebaseapp.com","messagingSenderId":"672419696322"})),],
  providers: [{ provide: RouteReuseStrategy, useClass: IonicRouteStrategy }],
  bootstrap: [AppComponent],
})
export class AppModule {}

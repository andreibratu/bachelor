import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { ClientFormComponent } from './client/components/client-form/client-form.component';
import {FormsModule} from '@angular/forms';
import { ClientCardComponent } from './client/components/client-card/client-card.component';
import { ClientCardListComponent } from './client/components/client-card-list/client-card-list.component';
import {HttpClientModule} from '@angular/common/http';
import { MovieFormComponent } from './movie/components/movie-form/movie-form.component';
import { MovieCardComponent } from './movie/components/movie-card/movie-card.component';
import { MovieCardListComponent } from './movie/components/movie-card-list/movie-card-list.component';
import { MovieEditModalComponent } from './movie/components/movie-edit-modal/movie-edit-modal.component';
import { ClientEditModalComponent } from './client/components/client-edit-modal/client-edit-modal.component';
import { FilterComponent } from './filter/component/filter.component';
import { SortComponent } from './sort/component/sort.component';
import { ClientContainerComponent } from './client/components/client-container/client-container.component';
import { MovieContainerComponent } from './movie/components/movie-container/movie-container.component';
import { RentalCardComponent } from './rental/components/rental-card/rental-card.component';
import { RentalCardListComponent } from './rental/components/rental-card-list/rental-card-list.component';
import { RentalContainerComponent } from './rental/components/rental-container/rental-container.component';
import {RentalFormComponent} from './rental/components/rental-form/rental-form.component';

@NgModule({
  declarations: [
    AppComponent,
    ClientFormComponent,
    ClientCardComponent,
    ClientCardListComponent,
    MovieFormComponent,
    MovieCardComponent,
    MovieCardListComponent,
    MovieEditModalComponent,
    MovieEditModalComponent,
    ClientEditModalComponent,
    FilterComponent,
    SortComponent,
    ClientContainerComponent,
    MovieContainerComponent,
    RentalCardComponent,
    RentalCardListComponent,
    RentalContainerComponent,
    RentalFormComponent,
  ],
    imports: [
        BrowserModule,
        NgbModule,
        FormsModule,
        HttpClientModule
    ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }

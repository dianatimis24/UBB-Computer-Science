import { Routes } from '@angular/router';
import { LoginComponent } from './components/login/login';
import { DashboardComponent } from './components/dashboard/dashboard';
import { HotelsComponent } from './components/hotels/hotels';
import { RoomsComponent } from './components/rooms/rooms';
import { ReservationsComponent } from './components/reservations/reservations';

export const routes: Routes = [
    { path: '', redirectTo: 'login', pathMatch: 'full' },
    { path: 'login', component: LoginComponent },
    { path: 'dashboard', component: DashboardComponent },
    { path: 'hotels', component: HotelsComponent },
    { path: 'rooms', component: RoomsComponent },
    { path: 'reservations', component: ReservationsComponent },
    { path: '**', redirectTo: 'login' }
];
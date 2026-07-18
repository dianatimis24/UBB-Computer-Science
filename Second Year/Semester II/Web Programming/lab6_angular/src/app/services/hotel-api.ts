import { Injectable, signal, computed } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Hotel } from '../models/hotel.model';
import { Room } from '../models/room.model';
import { Reservation } from '../models/reservation.model';
import { API_BASE } from '../config';

@Injectable({
  providedIn: 'root'
})
export class HotelApiService {

  private _username = signal<string>(localStorage.getItem('username') ?? '');

  readonly username = computed(() => this._username());
  readonly isLoggedIn = computed(() => this._username() !== '');

  setUsername(name: string): void {
    this._username.set(name);
    localStorage.setItem('username', name);
  }

  getUsername(): string {
    return this._username();
  }

  logout(): Observable<any> {
    this._username.set('');
    localStorage.removeItem('username');
    return this.http.post(
      `${API_BASE}/api/authentication/logout`, {}, { withCredentials: true }
    );
  }

  constructor(private http: HttpClient) { }

  checkLogin(username: string, password: string): Observable<any> {
    return this.http.post(
      `${API_BASE}/api/authentication/login`,
      { username, password },
      { withCredentials: true }
    );
  }

  getAllHotels(): Observable<Hotel[]> {
    return this.http.get<Hotel[]>(`${API_BASE}/api/hotels`, { withCredentials: true });
  }

  getHotelByName(name: string): Observable<Hotel[]> {
    return this.http.get<Hotel[]>(
      `${API_BASE}/api/hotels?name=${encodeURIComponent(name)}`,
      { withCredentials: true }
    );
  }

  getHotelByAddress(address: string): Observable<Hotel[]> {
    return this.http.get<Hotel[]>(
      `${API_BASE}/api/hotels?address=${encodeURIComponent(address)}`,
      { withCredentials: true }
    );
  }

  getHotelsByFilters(name?: string, address?: string): Observable<Hotel[]> {
    const params: string[] = [];
    if (name) params.push(`name=${encodeURIComponent(name)}`);
    if (address) params.push(`address=${encodeURIComponent(address)}`);
    const query = params.length > 0 ? `?${params.join('&')}` : '';
    return this.http.get<Hotel[]>(`${API_BASE}/api/hotels${query}`, { withCredentials: true });
  }

  insertHotel(name: string, address: string): Observable<any> {
    return this.http.post(`${API_BASE}/api/hotels`, { name, address }, { withCredentials: true });
  }

  updateHotel(id: number, name: string, address: string): Observable<any> {
    return this.http.put(`${API_BASE}/api/hotels/${id}`, { name, address }, { withCredentials: true });
  }

  deleteHotel(id: number): Observable<any> {
    return this.http.delete(`${API_BASE}/api/hotels/${id}`, { withCredentials: true });
  }

  getAllRooms(): Observable<Room[]> {
    return this.http.get<Room[]>(`${API_BASE}/api/rooms`, { withCredentials: true });
  }

  getRoomByCategory(category: string): Observable<Room[]> {
    return this.http.get<Room[]>(
      `${API_BASE}/api/rooms?category=${encodeURIComponent(category)}`,
      { withCredentials: true }
    );
  }

  getRoomByType(type: string): Observable<Room[]> {
    return this.http.get<Room[]>(
      `${API_BASE}/api/rooms?type=${encodeURIComponent(type)}`,
      { withCredentials: true }
    );
  }

  getRoomByPrice(price: number): Observable<Room[]> {
    return this.http.get<Room[]>(
      `${API_BASE}/api/rooms?maxPrice=${price}`,
      { withCredentials: true }
    );
  }

  getRoomByHotel(hotel_name: string): Observable<Room[]> {
    return this.http.get<Room[]>(
      `${API_BASE}/api/rooms?hotelName=${encodeURIComponent(hotel_name)}`,
      { withCredentials: true }
    );
  }

  getRoomsByFilters(
    category?: string,
    type?: string,
    maxPrice?: number,
    hotelName?: string
  ): Observable<Room[]> {
    const params: string[] = [];
    if (category) params.push(`category=${encodeURIComponent(category)}`);
    if (type) params.push(`type=${encodeURIComponent(type)}`);
    if (maxPrice) params.push(`maxPrice=${maxPrice}`);
    if (hotelName) params.push(`hotelName=${encodeURIComponent(hotelName)}`);
    const query = params.length > 0 ? `?${params.join('&')}` : '';
    return this.http.get<Room[]>(`${API_BASE}/api/rooms${query}`, { withCredentials: true });
  }

  insertRoom(hotel_id: number, room_number: string, category: string, type: string, price: number): Observable<any> {
    return this.http.post(
      `${API_BASE}/api/rooms`,
      { hotelId: hotel_id, roomNumber: room_number, category, type, price },
      { withCredentials: true }
    );
  }

  updateRoom(id: number, room_number: string, category: string, type: string, price: number): Observable<any> {
    return this.http.put(
      `${API_BASE}/api/rooms/${id}`,
      { roomNumber: room_number, category, type, price },
      { withCredentials: true }
    );
  }

  deleteRoom(id: number): Observable<any> {
    return this.http.delete(`${API_BASE}/api/rooms/${id}`, { withCredentials: true });
  }

  getReservationsByUsername(): Observable<Reservation[]> {
    return this.http.get<Reservation[]>(`${API_BASE}/api/reservations`, { withCredentials: true });
  }

  insertReservation(room_id: number, start_date: string, end_date: string): Observable<any> {
    return this.http.post(
      `${API_BASE}/api/reservations`,
      { roomId: room_id, startDate: start_date, endDate: end_date },
      { withCredentials: true }
    );
  }

  editReservation(id: number, start_date: string, end_date: string): Observable<any> {
    return this.http.put(
      `${API_BASE}/api/reservations/${id}`,
      { startDate: start_date, endDate: end_date },
      { withCredentials: true }
    );
  }

  deleteReservation(id: number): Observable<any> {
    return this.http.delete(`${API_BASE}/api/reservations/${id}`, { withCredentials: true });
  }
}
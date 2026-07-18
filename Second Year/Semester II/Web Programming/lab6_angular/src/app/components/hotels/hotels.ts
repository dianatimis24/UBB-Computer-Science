import { Component, OnInit, signal } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { HotelApiService } from '../../services/hotel-api';
import { Hotel } from '../../models/hotel.model';

@Component({
  selector: 'app-hotels',
  imports: [FormsModule],
  templateUrl: './hotels.html',
  styleUrl: './hotels.css'
})
export class HotelsComponent implements OnInit {

  hotels = signal<Hotel[]>([]);
  showModal = signal(false);
  isEditing = signal(false);
  filterName = signal('');
  filterAddress = signal('');
  modalName = signal('');
  modalAddress = signal('');
  editingId = signal(0);

  constructor(private api: HotelApiService, private router: Router) { }

  ngOnInit(): void {
    if (!this.api.isLoggedIn()) {
      this.router.navigate(['/login']);
      return;
    }
    this.loadHotels();
  }

  loadHotels(): void {
    this.api.getAllHotels().subscribe({
      next: (data) => this.hotels.set(data),
      error: () => alert('Could not load hotels.')
    });
  }

  applyFilters(): void {
    const name = this.filterName().trim();
    const address = this.filterAddress().trim();

    if (!name && !address) {
      this.loadHotels();
      return;
    }

    this.api.getHotelsByFilters(
      name || undefined,
      address || undefined
    ).subscribe({
      next: (data) => this.hotels.set(data),
      error: () => alert('Could not filter hotels.')
    });
  }

  onFilterNameChange(value: string): void {
    this.filterName.set(value);
    this.applyFilters();
  }

  onFilterAddressChange(value: string): void {
    this.filterAddress.set(value);
    this.applyFilters();
  }

  openAddModal(): void {
    this.isEditing.set(false);
    this.modalName.set('');
    this.modalAddress.set('');
    this.editingId.set(0);
    this.showModal.set(true);
  }

  openEditModal(hotel: Hotel): void {
    this.isEditing.set(true);
    this.modalName.set(hotel.name);
    this.modalAddress.set(hotel.address);
    this.editingId.set(hotel.id);
    this.showModal.set(true);
  }

  closeModal(): void {
    this.showModal.set(false);
  }

  saveHotel(): void {
    if (this.modalName().trim() === '' || this.modalAddress().trim() === '') {
      alert('Name and address cannot be empty.');
      return;
    }

    if (this.isEditing()) {
      this.api.updateHotel(this.editingId(), this.modalName(), this.modalAddress()).subscribe({
        next: () => { this.closeModal(); this.loadHotels(); },
        error: (err) => {
          if (err.status === 422) alert('Invalid hotel data.');
          else alert('Could not update hotel.');
        }
      });
    } else {
      this.api.insertHotel(this.modalName(), this.modalAddress()).subscribe({
        next: () => { this.closeModal(); this.loadHotels(); },
        error: (err) => {
          if (err.status === 422) alert('Invalid hotel data.');
          else alert('Could not add hotel.');
        }
      });
    }
  }

  deleteHotel(hotel: Hotel): void {
    if (!confirm(`Delete hotel "${hotel.name}"? All its rooms and reservations will also be deleted.`)) return;
    this.api.deleteHotel(hotel.id).subscribe({
      next: () => this.hotels.update(list => list.filter(h => h.id !== hotel.id)),
      error: (err) => {
        if (err.status === 422) alert('Invalid hotel ID.');
        else alert('Could not delete hotel.');
      }
    });
  }

  goToAddRoom(hotel: Hotel): void {
    this.router.navigate(['/rooms'], { queryParams: { hotel_id: hotel.id } });
  }
}
import { Component, OnInit, signal, computed } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { HotelApiService } from '../../services/hotel-api';
import { Room } from '../../models/room.model';

@Component({
  selector: 'app-rooms',
  imports: [FormsModule],
  templateUrl: './rooms.html',
  styleUrl: './rooms.css'
})
export class RoomsComponent implements OnInit {

  rooms = signal<Room[]>([]);
  selectedRoomIds = signal<Set<number>>(new Set());
  currentPage = signal(0);
  readonly pageSize = 4;

  filterCategory = signal('');
  filterType = signal('');
  filterPrice = signal('');
  filterHotel = signal('');

  bookStartDate = signal('');
  bookEndDate = signal('');
  bookingResult = signal('');
  bookingResultType = signal<'success' | 'error' | 'warning' | ''>('');

  showModal = signal(false);
  editingId = signal(0);
  modalRoomNumber = signal('');
  modalCategory = signal('');
  modalType = signal('');
  modalPrice = signal('');

  totalPages = computed(() =>
    Math.ceil(this.rooms().length / this.pageSize)
  );

  pagedRooms = computed(() => {
    const start = this.currentPage() * this.pageSize;
    return this.rooms().slice(start, start + this.pageSize);
  });

  get isLoggedIn(): boolean {
    return this.api.isLoggedIn();
  }

  constructor(private api: HotelApiService, private router: Router) { }

  ngOnInit(): void {
    if (!this.api.isLoggedIn()) {
      this.router.navigate(['/login']);
      return;
    }
    this.loadRooms();
  }

  loadRooms(): void {
    this.currentPage.set(0);
    this.api.getAllRooms().subscribe({
      next: (data) => this.rooms.set(data),
      error: () => alert('Could not load rooms.')
    });
  }

  applyFilters(): void {
    this.currentPage.set(0);

    const category = this.filterCategory().trim();
    const type = this.filterType().trim();
    const priceValue = this.filterPrice().trim();
    const hotelName = this.filterHotel().trim();

    const price = parseFloat(priceValue);
    const maxPrice = (!isNaN(price) && price > 0) ? price : undefined;

    if (!category && !type && maxPrice === undefined && !hotelName) {
      this.loadRooms();
      return;
    }

    this.api.getRoomsByFilters(
      category || undefined,
      type || undefined,
      maxPrice,
      hotelName || undefined
    ).subscribe({
      next: (data) => this.rooms.set(data),
      error: () => alert('Could not filter rooms.')
    });
  }

  onFilterCategoryChange(value: string): void {
    this.filterCategory.set(value);
    this.applyFilters();
  }

  onFilterTypeChange(value: string): void {
    this.filterType.set(value);
    this.applyFilters();
  }

  onFilterPriceChange(value: string): void {
    this.filterPrice.set(value);
    this.applyFilters();
  }

  onFilterHotelChange(value: string): void {
    this.filterHotel.set(value);
    this.applyFilters();
  }

  prevPage(): void {
    if (this.currentPage() > 0) this.currentPage.update(p => p - 1);
  }

  nextPage(): void {
    if (this.currentPage() < this.totalPages() - 1) this.currentPage.update(p => p + 1);
  }

  isSelected(id: number): boolean {
    return this.selectedRoomIds().has(id);
  }

  toggleSelection(id: number): void {
    this.selectedRoomIds.update(set => {
      const next = new Set(set);
      next.has(id) ? next.delete(id) : next.add(id);
      return next;
    });
  }

  bookSelected(): void {
    if (!this.api.isLoggedIn()) { this.router.navigate(['/login']); return; }
    if (this.selectedRoomIds().size === 0) { alert('Please select at least one room.'); return; }
    if (!this.bookStartDate() || !this.bookEndDate()) { alert('Please fill in both dates.'); return; }
    if (this.bookStartDate() >= this.bookEndDate()) { alert('Start date must be before end date.'); return; }

    const roomIds = Array.from(this.selectedRoomIds());
    this.bookingResult.set('Processing...');
    this.bookingResultType.set('');
    this.bookRoomsSequentially(roomIds, 0, 0, 0);
  }

  private bookRoomsSequentially(
    roomIds: number[],
    index: number,
    success: number,
    overlap: number
  ): void {
    if (index >= roomIds.length) {
      this.showBookingResult(success, overlap, roomIds.length);
      this.selectedRoomIds.set(new Set());
      return;
    }
    this.api.insertReservation(roomIds[index], this.bookStartDate(), this.bookEndDate()).subscribe({
      next: () => {
        this.bookRoomsSequentially(roomIds, index + 1, success + 1, overlap);
      },
      error: (err) => {
        if (err.status === 409) {
          this.bookRoomsSequentially(roomIds, index + 1, success, overlap + 1);
        } else {
          this.bookRoomsSequentially(roomIds, index + 1, success, overlap);
        }
      }
    });
  }

  private showBookingResult(success: number, overlap: number, total: number): void {
    if (success === total) {
      this.bookingResult.set(`✓ All ${total} room(s) booked successfully!`);
      this.bookingResultType.set('success');
    } else if (overlap === total) {
      this.bookingResult.set('✕ None of the selected rooms are available for those dates.');
      this.bookingResultType.set('error');
    } else if (success === 0) {
      this.bookingResult.set('✕ No rooms could be booked. Please try again.');
      this.bookingResultType.set('error');
    } else {
      let msg = `⚠ ${success} of ${total} room(s) booked.`;
      if (overlap > 0) msg += ` ${overlap} room(s) already reserved for those dates.`;
      this.bookingResult.set(msg);
      this.bookingResultType.set('warning');
    }
  }

  openEditModal(room: Room): void {
    this.editingId.set(room.id);
    this.modalRoomNumber.set(room.room_number);
    this.modalCategory.set(room.category);
    this.modalType.set(room.type);
    this.modalPrice.set(String(room.price));
    this.showModal.set(true);
  }

  closeModal(): void {
    this.showModal.set(false);
  }

  saveRoom(): void {
    const price = parseFloat(this.modalPrice());
    if (!this.modalRoomNumber() || !this.modalCategory() || !this.modalType()) {
      alert('Room number, category and type cannot be empty.'); return;
    }
    if (isNaN(price) || price <= 0) { alert('Please enter a valid price.'); return; }

    this.api.updateRoom(
      this.editingId(), this.modalRoomNumber(),
      this.modalCategory(), this.modalType(), price
    ).subscribe({
      next: () => { this.closeModal(); this.loadRooms(); },
      error: (err) => {
        if (err.status === 422) alert('Invalid room data.');
        else alert('Could not update room.');
      }
    });
  }

  deleteRoom(room: Room): void {
    if (!confirm(`Delete room ${room.room_number} at ${room.hotel_name}?`)) return;
    this.api.deleteRoom(room.id).subscribe({
      next: () => {
        this.rooms.update(list => list.filter(r => r.id !== room.id));
        if (this.currentPage() > 0 && this.currentPage() >= this.totalPages()) {
          this.currentPage.update(p => p - 1);
        }
      },
      error: (err) => {
        if (err.status === 422) alert('Invalid room ID.');
        else alert('Could not delete room.');
      }
    });
  }
}
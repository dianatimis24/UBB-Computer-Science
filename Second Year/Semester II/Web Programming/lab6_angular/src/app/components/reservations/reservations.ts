import { Component, OnInit, signal, computed } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { HotelApiService } from '../../services/hotel-api';
import { Reservation } from '../../models/reservation.model';

@Component({
  selector: 'app-reservations',
  imports: [FormsModule],
  templateUrl: './reservations.html',
  styleUrl: './reservations.css'
})
export class ReservationsComponent implements OnInit {

  reservations = signal<Reservation[]>([]);
  currentPage = signal(0);
  readonly pageSize = 4;

  showModal = signal(false);
  editingId = signal(0);
  modalStartDate = signal('');
  modalEndDate = signal('');

  totalPages = computed(() =>
    Math.ceil(this.reservations().length / this.pageSize)
  );

  pagedReservations = computed(() => {
    const start = this.currentPage() * this.pageSize;
    return this.reservations().slice(start, start + this.pageSize);
  });

  constructor(private api: HotelApiService, private router: Router) { }

  ngOnInit(): void {
    if (!this.api.isLoggedIn()) {
      this.router.navigate(['/login']);
      return;
    }
    this.loadReservations();
  }

  loadReservations(): void {
    this.api.getReservationsByUsername().subscribe({
      next: (data) => {
        this.reservations.set(data);
        this.currentPage.set(0);
      },
      error: () => alert('Could not load reservations.')
    });
  }

  prevPage(): void {
    if (this.currentPage() > 0) this.currentPage.update(p => p - 1);
  }

  nextPage(): void {
    if (this.currentPage() < this.totalPages() - 1) this.currentPage.update(p => p + 1);
  }

  openEditModal(reservation: Reservation): void {
    this.editingId.set(reservation.id);
    this.modalStartDate.set(reservation.start_date);
    this.modalEndDate.set(reservation.end_date);
    this.showModal.set(true);
  }

  closeModal(): void {
    this.showModal.set(false);
  }

  saveReservation(): void {
    if (!this.modalStartDate() || !this.modalEndDate()) {
      alert('Please fill in both dates.'); return;
    }
    if (this.modalStartDate() >= this.modalEndDate()) {
      alert('Start date must be before end date.'); return;
    }
    this.api.editReservation(
      this.editingId(), this.modalStartDate(), this.modalEndDate()
    ).subscribe({
      next: () => { this.closeModal(); this.loadReservations(); },
      error: (err) => {
        if (err.status === 422) alert('Invalid reservation data.');
        else alert('Could not update reservation.');
      }
    });
  }

  deleteReservation(reservation: Reservation): void {
    if (!confirm('Are you sure you want to delete this reservation?')) return;
    this.api.deleteReservation(reservation.id).subscribe({
      next: () => {
        this.reservations.update(list => list.filter(r => r.id !== reservation.id));
        if (this.currentPage() > 0 && this.currentPage() >= this.totalPages()) {
          this.currentPage.update(p => p - 1);
        }
      },
      error: (err) => {
        if (err.status === 422) alert('Invalid reservation ID.');
        else alert('Could not delete reservation.');
      }
    });
  }
}
import { Component, OnInit, computed } from '@angular/core';
import { Router, RouterLink } from '@angular/router';
import { HotelApiService } from '../../services/hotel-api';

@Component({
  selector: 'app-home',
  imports: [RouterLink],
  templateUrl: './dashboard.html',
  styleUrl: './dashboard.css'
})
export class DashboardComponent implements OnInit {
  username = computed(() => this.api.getUsername());

  constructor(private api: HotelApiService, private router: Router) { }

  ngOnInit(): void {
    if (!this.api.isLoggedIn()) {
      this.router.navigate(['/login']);
    }
  }
}
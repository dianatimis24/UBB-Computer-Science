import { Component, signal, OnInit } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { HotelApiService } from '../../services/hotel-api';

@Component({
  selector: 'app-login',
  imports: [FormsModule],
  templateUrl: './login.html',
  styleUrl: './login.css'
})
export class LoginComponent implements OnInit {
  username = signal('');
  password = signal('');
  errorMessage = signal('');

  constructor(private api: HotelApiService, private router: Router) { }

  ngOnInit(): void {
    if (this.api.isLoggedIn()) {
      this.router.navigate(['/dashboard']);
    }
  }

  onLogin(): void {
    if (this.username().trim() === '' || this.password().trim() === '') {
      this.errorMessage.set('Please fill in both fields.');
      return;
    }

    this.api.checkLogin(this.username(), this.password()).subscribe({
      next: (result) => {
        this.api.setUsername(result.username);
        this.router.navigate(['/dashboard']);
      },
      error: (err) => {
        if (err.status === 401 || err.status === 404) {
          this.errorMessage.set('Invalid username or password.');
        } else {
          this.errorMessage.set('Could not connect to server. Please try again.');
        }
      }
    });
  }
}
# Weather Station - Web Files

These files handle receiving data from the Arduino board and storing it in the MySQL database.

## Setup

1. Place all files from this folder (`/web`) into your local server directory (`htdocs` for XAMPP, `www` for WAMP, etc.) so they are accessible via `localhost`.

2. Make sure you have a MySQL database created (e.g., `weather_station`) and update the database credentials in the PHP files if needed.

## Notes

- `data.php` (or similar files) handle inserting temperature, humidity, pressure, and UV index into the database.  
- Make sure your table structure matches the expected fields: `date`, `temp`, `press`, `hum`, `uv`.
- Optional: Adjust the scripts to fit your database configuration (user, password, table name).

# Restaurant Billing System (C++17)

A clean, multi-file console app to manage restaurant orders and generate receipts. No CMake required.

## Features

- Category-grouped menu
- Add/remove/update items
- Subtotal, discount (percent or promo `SAVE10`), tax, service charge
- Split bill per guest
- Payment (cash change/card/UPI)
- Save receipt to `receipt.txt`

## Project structure

```
.
├─ include/
│  ├─ MenuItem.h
│  ├─ OrderItem.h
│  └─ RestaurantBillingSystem.h
├─ src/
│  ├─ RestaurantBillingSystem.cpp
│  └─ main.cpp
└─ README.md
```

## Build and run

Windows (PowerShell):

```powershell
g++ -std=c++17 -O2 -Iinclude src\RestaurantBillingSystem.cpp src\main.cpp -o RestaurantBillingSystem.exe
.\RestaurantBillingSystem.exe
```

Linux/macOS:

```bash
g++ -std=c++17 -O2 -Iinclude src/RestaurantBillingSystem.cpp src/main.cpp -o RestaurantBillingSystem
./RestaurantBillingSystem
```

If `g++` is missing:

- Windows: install MinGW-w64 or MSYS2, then reopen the terminal.
- macOS: `xcode-select --install`
- Ubuntu/Debian: `sudo apt install g++`

## Usage

- 1: View Menu
- 2: Add Item (by ID, with quantity)
- 3: View Current Order
- 4: Remove Item (by ID)
- 5: Generate Bill (discount, tax, service, payment, split, receipt)
- 6: Clear Order
- 7: Update Item Quantity
- 8: Apply Discount (percent or `SAVE10`)
- 9: Configure Tax/Service rates
- 10: Exit

## Customize

- Menu items: edit `initializeMenu()` in `src/RestaurantBillingSystem.cpp`.
- Default tax/service: set in the `RestaurantBillingSystem` constructor.
- Receipt file: `receipt.txt` in the working directory.

## License

MIT (or your preferred license).

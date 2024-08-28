-- Keep a log of any SQL queries you execute as you solve the mystery.

-- I want to know what information are contained in this database
.table

-- I would like to start from the crime_scene_report so that I could know more about the crime info
.schema crime_scene_report
SELECT description FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Now we know that the theft took place at 10:15am at Humphrey Street bakery. There're three witnesses and took the interviews.

-- We need to look further into the three interviews to get more info about the theft
.schema interviews
SELECT name, transcript FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- We may need to look into bakery security logs from 10:15am to 10:25am to get info about theif's car
.schema bakery_security_logs
SELECT minute, activity, license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15;
-- There are 8 cars that are suspicious, all of them are exiting at the time slot

-- Look into the eight people according to the license_plate
.schema people
-- We would like to make sure one license_plate will be associated with only one person
SELECT COUNT(license_plate) FROM people; -- 177
SELECT COUNT(id) FROM people; -- 200
SELECT COUNT(id) FROM people WHERE license_plate IS NULL; -- 23
-- Now we look for those 8 people
SELECT name FROM people
WHERE license_plate IN(
SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25)
ORDER BY name ASC;
-- Now we have a long list of suspect: Barry, Bruce, Diana, Iman, Kelsey, Luca, Sofia, Vanessa

-- Check ATM on Leggett Street before 10:15am that day and see who is withdrawing money, this will help us narrow down the thief
.schema atm_transactions
SELECT account_number FROM atm_transactions
WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- There are also 8 people let's see who they are
SELECT name from people
WHERE id IN(
SELECT person_id FROM bank_accounts
WHERE account_number IN(
SELECT account_number FROM atm_transactions
WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
ORDER BY name ASC;
-- Now we got a new long list: Benista, Brooke, Bruce, Diana, Iman, Kenny, Luca, Taylor
-- Let's compare to find the common person among the two list: Bruce, Diana, Iman, Luca. The suspects have been narrowed down to 4 people.

-- Check phone call history around 10:15am-10:16am(less than 1 minute), it could be thief and accomplice, this will help us narrow down the thief
.schema phone_calls
SELECT caller, receiver FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;
-- Let's find the callers(thief) and the receivers(accomplice)
SELECT name FROM people
WHERE phone_number IN(
SELECT caller FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60)
ORDER BY name ASC;
-- Callers: Benista, Bruce, Carina, Diana, Kelsey, Kenny, Sofia, Taylor
-- Compare with the 4 people list to find the common person: Bruce and Diana. Now we narrow down to 2 suspects.
SELECT name FROM people
WHERE phone_number IN(
SELECT receiver FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60)
ORDER BY name ASC;
-- Receiver: Anna, Doris, Jack, Jacqueline, James, Larry, Melissa, Philip, Robin

-- Check the earliest flight out of town on July 29, that's the filght they are taking
.schema flights
SELECT * FROM airports;
SELECT * FROM flights
WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = 8
ORDER BY hour ASC, minute ASC LIMIT 1;
-- Cross reference the airports info: Their destination is 4 LaGuardia Airport, New York City. Flight ID 36.
-- Let's find who's taking that flight
SELECT passport_number FROM passengers
WHERE flight_id = (
SELECT id FROM flights
WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = 8
ORDER BY hour ASC, minute ASC LIMIT 1);
-- Now we have: Bruce, Doris, Edward, Kelsey, Kenny, Luca, Sofia, Taylor
-- Compare this with 2 suspect theif list we got: Bruce is the thief.

-- Now let's see who is Bruce call receiver
SELECT pc.name AS caller, pr.name AS receiver, ph.duration
FROM phone_calls ph
JOIN people pc ON ph.caller = pc.phone_number
JOIN people pr ON ph.receiver = pr.phone_number
WHERE year = 2023 AND month = 7 AND day = 28 AND ph.duration < 60;
-- Now we see Robin is the accomplice.
-- Destination is New York City.


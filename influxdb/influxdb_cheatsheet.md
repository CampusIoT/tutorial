# CampusIoT :: InfluxDB Cheatsheet

[Docs](https://docs.influxdata.com/influxdb/v1.8/query_language/spec/#queries)

## Connect to the container
```bash
docker-compose exec influxdb bash
```

```bash
influx
```

## Help
```
HELP
```

## Databases
```
SHOW DATABASES

-- select the lorawan database
USE lorawan

-- show the retention policies
SHOW RETENTION POLICIES
```

## Show measurements
```
-- show all measurements
SHOW MEASUREMENTS

-- show measurements that start with 'dat'
SHOW MEASUREMENTS WITH MEASUREMENT =~ /^dat.*/
```

```
-- show estimated cardinality of measurement set on current database
SHOW MEASUREMENT CARDINALITY

-- show exact cardinality of measurement set on specified database
SHOW MEASUREMENT EXACT CARDINALITY ON lorawan
```

## Show tags
```
-- show all tag keys
SHOW TAG KEYS

-- show all tag keys from the data measurement
SHOW TAG KEYS FROM "data"

-- show all tag keys from the data measurement where the deviceName starts with 'SICONIA'
SHOW TAG KEYS FROM "data" WHERE "deviceName" =~ /^SICONIA.*/
```

```
-- show estimated tag key values cardinality for a specified tag key
SHOW TAG VALUES CARDINALITY WITH KEY = "devEUI"
SHOW TAG VALUES CARDINALITY WITH KEY = "applicationID"

-- show estimated tag key values cardinality for a specified tag key
SHOW TAG VALUES CARDINALITY FROM "data" WITH KEY = "devEUI"
SHOW TAG VALUES CARDINALITY FROM "data" WITH KEY = "applicationID"


-- show exact tag key values cardinality for a specified tag key
SHOW TAG VALUES EXACT CARDINALITY WITH KEY = "devEUI"
SHOW TAG VALUES EXACT CARDINALITY WITH KEY = "applicationID"

-- show exact tag key values cardinality for a specified tag key
SHOW TAG VALUES EXACT CARDINALITY FROM "data" WITH KEY = "devEUI"
SHOW TAG VALUES EXACT CARDINALITY FROM "data" WITH KEY = "applicationID"
```

## Show fields
```
-- show all field keys
SHOW FIELD KEYS

-- show all field keys from the data measurement
SHOW FIELD KEYS FROM "data"

```

```
-- show all tag fields cardinality
SHOW FIELD KEY CARDINALITY
SHOW FIELD KEY EXACT CARDINALITY
```

## Show series
```
-- show the series on current database
SHOW SERIES

-- show the series from the data measurement
SHOW SERIES FROM "data"
SHOW SERIES FROM "sixty_days"."data"
SHOW SERIES FROM "lorawan"."sixty_days"."data"

-- show all series from the data measurement where the deviceName starts with 'SICONIA'
SHOW SERIES FROM "data" WHERE "deviceName" =~ /^SICONIA.*/
```

```
-- show estimated cardinality of the series on current database
SHOW SERIES CARDINALITY
-- show estimated cardinality of the series on specified database
SHOW SERIES CARDINALITY ON lorawan
-- show exact series cardinality
SHOW SERIES EXACT CARDINALITY
-- show series cardinality of the series on specified database
SHOW SERIES EXACT CARDINALITY ON lorawan
```

## Queries
```
SELECT COUNT(*) FROM "data"

SELECT COUNT(*) FROM "data" GROUP BY "devEUI"

SELECT COUNT(*) FROM "data" WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY "deviceName"

SELECT MIN(temperature) AS min_temp, MAX(temperature) AS max_temp, MIN(humidity) AS min_hum, MAX(humidity) AS max_hum FROM "data" WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY "deviceName"

SELECT LAST(temperature) AS last_temp, LAST(humidity) AS last_hum FROM "data" WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY "deviceName"

SELECT MEAN(temperature) AS mean_temp FROM data WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY "deviceName"

SELECT MEAN(temperature AS mean_temp, MEAN(humidity) AS mean_hum FROM data WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY time(1h)

SELECT MEAN(temperature) AS mean_temp, MEAN(humidity) AS mean_hum FROM data WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY time(1d)

SELECT MEAN(temperature) AS mean_temp, MEAN(humidity) AS mean_hum FROM data WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY time(1d)

SELECT MEAN(temperature) AS mean_temp, MEAN(humidity) AS mean_hum, MIN(temperature) AS min_temp, MAX(temperature) AS max_temp, MIN(humidity) AS min_hum, MAX(humidity) AS max_hum FROM data WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY "deviceName", time(1d)
```

## Explain queries
```
EXPLAIN SELECT COUNT(*) FROM "data" WHERE "deviceName" =~ /^SICONIA.*/ GROUP BY "devEUI"
EXPLAIN SELECT MEAN(temperature) FROM "data" GROUP BY "devEUI"
EXPLAIN ANALYZE SELECT MEAN(temperature) FROM "data" GROUP BY "devEUI"
```


## Continuous queries
```
-- this customizes the resample interval so the interval is queried every 1m and intervals are resampled until 10m after their start time
-- when resample is used, at least one of "EVERY" or "FOR" must be used
CREATE CONTINUOUS QUERY "temperature_mean"
ON "lorawan"
RESAMPLE EVERY 1m FOR 10m
BEGIN
  SELECT mean("temperature")
  INTO "temperature_mean"
  FROM "data"
  GROUP BY time(1m)
END;


-- show all continuous queries
SHOW CONTINUOUS QUERIES
```

## Misc
```
-- show all users
SHOW USERS
```

```
-- show all currently-running queries
SHOW QUERIES
-- show all continuous queries
SHOW CONTINUOUS QUERIES
```

```
-- show all retention policies on a database
SHOW RETENTION POLICIES ON "lorawan"
```

```
SHOW SHARD GROUPS
SHOW SHARDS
```

```
SHOW STATS
```

```
SHOW DIAGNOSTICS
```

```
-- Subscriptions tell InfluxDB to send all the data it receives to Kapacitor.
-- Create a SUBSCRIPTION on database 'lorawan' and retention policy 'sixty_days' that send data to 'kapacitor:9090' via UDP.
CREATE SUBSCRIPTION "sub0" ON "lorawan"."sixty_days" DESTINATIONS ALL 'udp://kapacitor:9090'

SHOW SUBSCRIPTIONS
```

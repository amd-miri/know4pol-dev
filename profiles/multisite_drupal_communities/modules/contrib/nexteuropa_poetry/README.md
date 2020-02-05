# NextEuropa Poetry

[![Build Status](https://travis-ci.org/ec-europa/nexteuropa_poetry.svg?branch=master)](https://travis-ci.org/ec-europa/nexteuropa_poetry)

## Development setup

Run:

```
$ composer install
```

This will download all development dependencies and build a Drupal 7 target site under `./build` and run
`./vendor/bin/run drupal:site-setup` to setup proper symlink and produce necessary scaffolding files.

After that:

1. Copy `runner.yml.dist` into `runner.yml` and customise relevant parameters.
2. Run `./vendor/bin/run drupal:site-install` to install the project having the NextEuropa Poetry module enabled.

To have a complete list of building options run:

```
$ ./vendor/bin/run
```

## Configuration

After installing the module a new administration page will be available in `admin/config/regional/poetry-client`.

For the `Remote service` (Poetry) Username and Password, and the `Notification handler` (Callback) Username and Password, 
use the same credentials as for the [DGT Connector](https://github.com/ec-europa/platform-dev/tree/release-2.5/profiles/common/modules/features/nexteuropa_dgt_connector#user-content-general-settings-see-dgt-reference-explanation)

Set the following value for `Service WSDL` according to your environment:

- Production: `http://intragate.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl`
- Testing: `http://intragate.test.ec.europa.eu/DGT/poetry_services/components/poetry.cfc?wsdl`

## Usage

The following code will give you a Poetry Client object:

```php
$poetry = nexteuropa_poetry_client();
```

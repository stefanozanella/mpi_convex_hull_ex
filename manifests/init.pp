$mpi_pkgs = [
  'libopenmpi1.6',
  'libopenmpi1.6-dev',
  'openmpi1.6-bin',
]

package { $mpi_pkgs:
  ensure => installed,
}

package { 'ntp':
  ensure => installed,
  before => Service['ntp'],
}

service { 'ntp':
  ensure => running,
  enable => true,
}

exec { 'apt-get update':
  command => '/usr/bin/apt-get update',
}

Package {
  require => Exec['apt-get update'],
}
